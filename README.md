# Cabinet Controller

## Prerequisties

    brew install platformio

## USB

Upload & Monitor:

    pio run -e usb -t upload -t monitor
    
Monitor:

    pio run -e usb -t monitor
    
## OTA

PlatformIO OTA Info: https://docs.platformio.org/en/latest/platforms/espressif32.html#over-the-air-ota-update

Upload:

    pio run -e ota -t upload
    
Upload and Monitor (with USB connected):

    pio run -e ota -t upload && pio run -e usb -t monitor


## Notes

PlatformIO Documentation: https://docs.platformio.org/en/latest/quickstart.html

Install Library: pio lib install "FastLED"
wESP Documentation: https://wesp32.com/software/