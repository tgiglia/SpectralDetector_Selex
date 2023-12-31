//
// Copyright 2010-2011,2014 Ettus Research LLC
// Copyright 2018 Ettus Research, a National Instruments Company
//
// SPDX-License-Identifier: GPL-3.0-or-later
//

#include "ascii_art_dft.hpp" //implementation
#include "RESTUtils.hpp"

#include "Logger.hpp"
#include "EOCXmlMaker.hpp"
#include "ConfigData.hpp"
#include "DetectionConsumer.hpp"
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/utils/safe_main.hpp>
#include <uhd/utils/thread.hpp>
#include <curses.h>
#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <chrono>
#include <complex>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace po = boost::program_options;
using std::chrono::high_resolution_clock;


void runJammerDetection(uhd::rx_streamer::sptr rx_stream,uhd::rx_metadata_t md,std::vector<std::complex<float>> buff);
void runFullCurses(uhd::rx_streamer::sptr rx_stream,uhd::rx_metadata_t md,std::vector<std::complex<float>> buff);
void runRESTTest(std::string sHost,std::string sPort);
void signalHandler(int signal);


void signalHandler(int signal) {
    if (signal == SIGTERM) {
        // Cleanup tasks before terminating the daemon
        // Close files, release resources, etc.
        std::cout << "Service is terminating..." << std::endl;
        logDbgWithTime("spectral.dbg","Service is terminating...");
        // Perform necessary cleanup and exit
        exit(0);
    }
}


int daemonize(std::string dbgFile) 
{
    logDbgWithTime(dbgFile,"Start of daemonize.");
    // Fork the current process
    pid_t pid = fork();

    // If fork failed, exit with an error
    if (pid < 0) {
        std::cerr << "Failed to fork the process." << std::endl;
        logDbgWithTime(dbgFile,"Failed to fork the process.");
        return 1;
    }

    // If it's the parent process, exit successfully
    if (pid > 0) {
        return 0;
    }
    logDbgWithTime(dbgFile,"daemonize: setting umask");
    // Set the file mode creation mask
    umask(0);
    logDbgWithTime(dbgFile,"daemonize: setting new session for child process.");
    // Create a new session for the child process
    pid_t sid = setsid();
    if (sid < 0) {
        std::cerr << "Failed to create a new session." << std::endl;
        logDbgWithTime(dbgFile,"Failed to create a new session.");
        return 1;
    }
    logDbgWithTime(dbgFile,"daemonize: changing working directory.");
    // Change the working directory to a suitable location
    if (chdir("/") < 0) {
        std::cerr << "Failed to change the working directory." << std::endl;
        logDbgWithTime(dbgFile,"Failed to change the working directory");
        return 1;
    }
    
    // Define signal handlers for SIGTERM (termination signal)
    logDbgWithTime(dbgFile,"Installing the signal handler...");
    signal(SIGTERM, signalHandler);
    logDbgWithTime(dbgFile,"daemonize: closing standard file descriptors.");
    
    // Close the standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    
    
    return 0;
    
}

void ConsumerThreadFunction(ConfigData cd) {
    DetectionConsumer detectionConsumer;
    detectionConsumer.run(cd);



}

int UHD_SAFE_MAIN(int argc, char* argv[])
{
    // variables to be set by po
    std::string args, ant, subdev, ref;
    size_t num_bins,num_jammer_bins;
    int eocPort;
    int iDaemonFlg;
    double rate, freq, gain, bw, frame_rate, step;
    float ref_lvl, dyn_rng,jammerThreshold;
    bool show_controls;
    std::string jammerDbgFile;
    
    std::string eocHost;
    std::string dbgFile = "spectral.dbg";
    std::string cfgFile = "/home/tgiglia/Documents/SpectralDetectorConfig.xml";
    std::string notificationsFile;
    stringstream ssTmp;
    //http://192.168.1.71:5000/echo/
    //runRESTTest("192.168.1.71","5000");

    // setup the program options
    po::options_description desc("Allowed options");
    // clang-format off
    desc.add_options()
        ("help", "help message")
        ("args", po::value<std::string>(&args)->default_value(""), "multi uhd device address args")
        // hardware parameters
        ("rate", po::value<double>(&rate), "rate of incoming samples (sps)")
        ("freq", po::value<double>(&freq), "RF center frequency in Hz")
        ("gain", po::value<double>(&gain), "gain for the RF chain")
        ("ant", po::value<std::string>(&ant), "antenna selection")
        ("subdev", po::value<std::string>(&subdev), "subdevice specification")
        ("bw", po::value<double>(&bw), "analog frontend filter bandwidth in Hz")
        // display parameters
        ("num-bins", po::value<size_t>(&num_bins)->default_value(512), "the number of bins in the DFT")
        ("frame-rate", po::value<double>(&frame_rate)->default_value(1), "frame rate of the display (fps)")
        ("ref-lvl", po::value<float>(&ref_lvl)->default_value(0), "reference level for the display (dB)")
        ("dyn-rng", po::value<float>(&dyn_rng)->default_value(60), "dynamic range for the display (dB)")
        ("ref", po::value<std::string>(&ref)->default_value("internal"), "reference source (internal, external, mimo)")
        ("step", po::value<double>(&step)->default_value(1e6), "tuning step for rate/bw/freq")
        ("show-controls", po::value<bool>(&show_controls)->default_value(true), "show the keyboard controls")
        ("int-n", "tune USRP with integer-N tuning")
        ("jammer-thresh", po::value<float>(&jammerThreshold)->default_value(10.0),"threshold for jammer detection")
        ("jammer-bins", po::value<size_t>(&num_jammer_bins)->default_value(10), "number of bins for jammer bandwidth")
        ("xml-path",po::value<std::string>(&cfgFile)->default_value("./SpectralDetectorConfig.xml"),"file name of the config file")
        
  
        ("daemon",po::value<int>(&iDaemonFlg)->default_value(1),"daemon flag set to 0 for daemon.")
        
    ;
    // clang-format on
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    // print the help message
    if (vm.count("help") or not vm.count("rate")) {
        
        ssTmp<< boost::format("UHD RX ASCII Art DFT %s") % desc << std::endl;
        std::cout << ssTmp.str();
        
        logDbgWithTime(dbgFile,ssTmp.str());
        return EXIT_FAILURE;
    }

    
    int iKeepGoing = 0;
    //xmlTest("/home/tgiglia/Desktop/Share/test.xml","/home/tgiglia/Desktop/Share/out.xml");
    /*ReadAlarmXMLMaker ra;
    ra.testAlarmXML();*/
    
    ConfigData cd;
    if(cd.loadConfig(cfgFile,dbgFile)){
        //std::cout<<"CONFIG:"<<endl<<cd.showConfig()<<endl;
        stringstream ss;
        ss<<"\nConfig\n"<<cd.showConfig()<<endl;
        logDbgWithTime(dbgFile,ss.str());

    }
    else {
        std::cout<<"ERROR Could not load XML file."<<endl;
        logDbgWithTime(dbgFile,"ERROR Could not load XML file...");
        return 0;
    }
    jammerDbgFile = cd.li.jammerDbg;
    notificationsFile = cd.li.notificationDbg;
    dbgFile = cd.li.spectralDbg;

    if(iKeepGoing == 1) 
    {
        return 0;
    }

    
    // create a usrp device
    ssTmp << std::endl;
    ssTmp << boost::format("Creating the usrp device with: %s...") % args
              << std::endl;
    logDbgWithTime(dbgFile,ssTmp.str());
    /*std::cout << std::endl;
    std::cout << boost::format("Creating the usrp device with: %s...") % args
              << std::endl;*/
    uhd::usrp::multi_usrp::sptr usrp = uhd::usrp::multi_usrp::make(args);

    // Lock mboard clocks
    if (vm.count("ref")) {
        usrp->set_clock_source(ref);
    }

    // always select the subdevice first, the channel mapping affects the other settings
    if (vm.count("subdev"))
        usrp->set_rx_subdev_spec(subdev);
    ssTmp.str("");
    ssTmp << boost::format("Using Device: %s") % usrp->get_pp_string() << std::endl;
    logDbgWithTime(dbgFile,ssTmp.str());

    // set the sample rate
    if (not vm.count("rate")) {
        ssTmp.str("");
        ssTmp << "Please specify the sample rate with --rate" << std::endl;
        logDbgWithTime(dbgFile,ssTmp.str());
        return EXIT_FAILURE;
    }
    ssTmp.str("");
    ssTmp << boost::format("Setting RX Rate: %f Msps...") % (rate / 1e6) << std::endl;
    logDbgWithTime(dbgFile,ssTmp.str());
    usrp->set_rx_rate(rate);
    ssTmp.str("");
    ssTmp << boost::format("Actual RX Rate: %f Msps...") % (usrp->get_rx_rate() / 1e6)
              << std::endl
              << std::endl;
    logDbgWithTime(dbgFile,ssTmp.str());

    // set the center frequency
    if (not vm.count("freq")) {
        ssTmp.str("");
        ssTmp << "Please specify the center frequency with --freq" << std::endl;
        logDbgWithTime(dbgFile,ssTmp.str());
        return EXIT_FAILURE;
    }
    ssTmp.str("");
    ssTmp << boost::format("Setting RX Freq: %f MHz...") % (freq / 1e6) << std::endl;
    logDbgWithTime(dbgFile,ssTmp.str());
    uhd::tune_request_t tune_request(freq);
    if (vm.count("int-n"))
        tune_request.args = uhd::device_addr_t("mode_n=integer");
    usrp->set_rx_freq(tune_request);
    ssTmp.str("");
    ssTmp << boost::format("Actual RX Freq: %f MHz...") % (usrp->get_rx_freq() / 1e6)
              << std::endl
              << std::endl;
    logDbgWithTime(dbgFile,ssTmp.str());

    // set the rf gain
    if (vm.count("gain")) {
        ssTmp.str("");
        ssTmp << boost::format("Setting RX Gain: %f dB...") % gain << std::endl;
        logDbgWithTime(dbgFile,ssTmp.str());
        usrp->set_rx_gain(gain);
        ssTmp.str("");
        ssTmp << boost::format("Actual RX Gain: %f dB...") % usrp->get_rx_gain()
                  << std::endl
                  << std::endl;
        logDbgWithTime(dbgFile,ssTmp.str());
    } else {
        gain = usrp->get_rx_gain();
    }

    // set the analog frontend filter bandwidth
    if (vm.count("bw")) {
        ssTmp.str("");
        ssTmp << boost::format("Setting RX Bandwidth: %f MHz...") % (bw / 1e6)
                  << std::endl;
        logDbgWithTime(dbgFile,ssTmp.str());
        usrp->set_rx_bandwidth(bw);
        ssTmp.str("");
        ssTmp << boost::format("Actual RX Bandwidth: %f MHz...")
                         % (usrp->get_rx_bandwidth() / 1e6)
                  << std::endl
                  << std::endl;
        logDbgWithTime(dbgFile,ssTmp.str());
    } else {
        bw = usrp->get_rx_bandwidth();
    }

    // set the antenna
    if (vm.count("ant"))
        usrp->set_rx_antenna(ant);

    std::this_thread::sleep_for(std::chrono::seconds(1)); // allow for some setup time

    // Check Ref and LO Lock detect
    std::vector<std::string> sensor_names;
    sensor_names = usrp->get_rx_sensor_names(0);
    if (std::find(sensor_names.begin(), sensor_names.end(), "lo_locked")
        != sensor_names.end()) {
        uhd::sensor_value_t lo_locked = usrp->get_rx_sensor("lo_locked", 0);
        ssTmp.str("");
        ssTmp << boost::format("Checking RX: %s ...") % lo_locked.to_pp_string()
                  << std::endl;
        logDbgWithTime(dbgFile,ssTmp.str());
        UHD_ASSERT_THROW(lo_locked.to_bool());
    }
    sensor_names = usrp->get_mboard_sensor_names(0);
    if ((ref == "mimo")
        and (std::find(sensor_names.begin(), sensor_names.end(), "mimo_locked")
                != sensor_names.end())) {
        uhd::sensor_value_t mimo_locked = usrp->get_mboard_sensor("mimo_locked", 0);
        ssTmp.str("");
        ssTmp << boost::format("Checking RX: %s ...") % mimo_locked.to_pp_string()
                  << std::endl;
        logDbgWithTime(dbgFile,ssTmp.str());
        UHD_ASSERT_THROW(mimo_locked.to_bool());
    }
    if ((ref == "external")
        and (std::find(sensor_names.begin(), sensor_names.end(), "ref_locked")
                != sensor_names.end())) {
        uhd::sensor_value_t ref_locked = usrp->get_mboard_sensor("ref_locked", 0);
        ssTmp.str("");
        ssTmp << boost::format("Checking RX: %s ...") % ref_locked.to_pp_string()
                  << std::endl;
        logDbgWithTime(dbgFile,ssTmp.str());
        UHD_ASSERT_THROW(ref_locked.to_bool());
    }

    // create a receive streamer
    uhd::stream_args_t stream_args("fc32"); // complex floats
    uhd::rx_streamer::sptr rx_stream = usrp->get_rx_stream(stream_args);

    // allocate recv buffer and metatdata
    uhd::rx_metadata_t md;
    std::vector<std::complex<float>> buff(num_bins);
    
    //------------------------------------------------------------------
    //-- Initialize
    //------------------------------------------------------------------
    std::stringstream ssDbg;
    
    //initscr(); // curses init
    
    size_t stCols = 126;
    size_t stLines = 37;
    /*ssDbg<<"COLS: "<<stCols<<" LINES: "<<stLines<<std::endl;
    logDbgWithTime(dbgFile,ssDbg.str());*/
    rx_stream->issue_stream_cmd(uhd::stream_cmd_t::STREAM_MODE_START_CONTINUOUS);
    auto next_refresh = high_resolution_clock::now();
    
    if(iDaemonFlg == 0) {
            //OK LETS DAEMONIZE
            logDbgWithTime(dbgFile,"About to daemonize....");
            daemonize(dbgFile);
            logDbgWithTime(dbgFile,"Afterdaemonize....");
    }

    //Setup the Consumer thread
    SingletonBoolean sb = SingletonBoolean::getInstance();
    sb.keepGoing->setTrue();
    std::thread consumerThr([cd]() {
        ConsumerThreadFunction(cd);
    });
    //
    //------------------------------------------------------------------
    //-- Main loop
    //------------------------------------------------------------------
    while (true) {
        // read a buffer's worth of samples every iteration
        
        size_t num_rx_samps = rx_stream->recv(&buff.front(), buff.size(), md);
        if (num_rx_samps != buff.size())
            continue;
        
        // check and update the display refresh condition
        if (high_resolution_clock::now() < next_refresh) {
            continue;
        }
        
        next_refresh = high_resolution_clock::now()
                       + std::chrono::microseconds(int64_t(1e6 / frame_rate));
        
        // calculate the dft and create the ascii art frame
        ascii_art_dft::log_pwr_dft_type lpdft(
            ascii_art_dft::log_pwr_dft(&buff.front(), num_rx_samps));
        
        
        std::string frame = ascii_art_dft::scan_for_jammer(lpdft,
            stCols,
            (show_controls ? stLines - 6 : stLines),
            usrp->get_rx_rate(),
            usrp->get_rx_freq(),
            dyn_rng,
            ref_lvl,
            jammerThreshold,
            num_jammer_bins,
            jammerDbgFile,cd);
        
        std::string border = std::string((COLS), '-');

        
        
        // curses screen handling: clear and print frame
        /*clear();
       
        printw("%s", frame.c_str());*/

        
        // curses key handling: no timeout, any key to exit
        timeout(0);
        int ch = getch();
        
    }
    sb.keepGoing->setFalse();
    consumerThr.join();
    
    //------------------------------------------------------------------
    //-- Cleanup
    //------------------------------------------------------------------
    rx_stream->issue_stream_cmd(uhd::stream_cmd_t::STREAM_MODE_STOP_CONTINUOUS);
    //endwin(); // curses done

    // finished
    std::cout << std::endl << "Done!" << std::endl << std::endl;
    
    return EXIT_SUCCESS;
}

void runRESTTest(std::string sHost,std::string sPort)
{
    RESTUtils ru;
    
    //std::string sBody = "{\"start_year\":2017}";
    std::string sBody = R"({"param1": "value1", "param2": "value2"})";
    
    ru.testRESTPost(sHost,sPort,sBody);
    
    
}

