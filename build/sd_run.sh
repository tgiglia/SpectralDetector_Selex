#!/bin/bash

/home/tgiglia/projects/SpectralDetector/build/SpectralDetector --freq 1575.42e6 --rate 2e6 --gain 38 --bw 2e6 --ref-lvl -30 --jammer-thresh 14.0 --jammer-bins 10 --jammer-debug /home/tgiglia/projects/SpectralDetector/build/Jammer.dbg --notification-path /home/tgiglia/projects/SpectralDetector/build/Notifications.txt --debug-path /home/tgiglia/projects/SpectralDetector/build/spectral.dbg --daemon 1 --xml-path /home/tgiglia/Documents/SpectralDetectorConfig.xml

