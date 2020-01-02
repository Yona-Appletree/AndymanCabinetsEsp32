EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	9050 2200 9150 2200
Wire Wire Line
	9150 2200 9150 2450
Wire Wire Line
	9150 2100 9150 2150
Wire Wire Line
	9150 1700 9050 1700
Wire Wire Line
	9150 1450 9150 1700
Wire Wire Line
	9150 1800 9050 1800
Wire Wire Line
	9150 1750 9150 1800
Wire Wire Line
	9150 2100 9050 2100
Wire Wire Line
	9200 2450 9200 2700
Wire Wire Line
	9150 2450 9200 2450
Wire Wire Line
	9200 2150 9200 2400
Wire Wire Line
	9150 2150 9200 2150
Wire Wire Line
	9200 2000 9200 2100
Wire Wire Line
	9200 1450 9150 1450
Wire Wire Line
	9200 1200 9200 1450
Wire Wire Line
	9200 1750 9150 1750
Wire Wire Line
	9200 1500 9200 1750
Wire Wire Line
	9200 1900 9050 1900
Wire Wire Line
	9200 1800 9200 1900
Wire Wire Line
	9200 2000 9050 2000
Connection ~ 9300 2700
$Comp
L power:GNDD #PWR03
U 1 1 5DAF1443
P 9300 2700
F 0 "#PWR03" H 9300 2450 50  0001 C CNN
F 1 "GNDD" H 9304 2545 50  0000 C CNN
F 2 "" H 9300 2700 50  0001 C CNN
F 3 "" H 9300 2700 50  0001 C CNN
	1    9300 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 2700 9300 2700
Connection ~ 9300 2400
Wire Wire Line
	9200 2400 9300 2400
Connection ~ 9300 2100
Wire Wire Line
	9200 2100 9300 2100
Wire Wire Line
	9300 1200 9200 1200
Connection ~ 9300 1500
Wire Wire Line
	9300 1500 9200 1500
Connection ~ 9300 1800
Wire Wire Line
	9300 1800 9200 1800
$Comp
L Device:R R5
U 1 1 5DAEA2B3
P 9300 2550
F 0 "R5" H 9230 2504 50  0000 R CNN
F 1 "1K" H 9230 2595 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9230 2550 50  0001 C CNN
F 3 "~" H 9300 2550 50  0001 C CNN
	1    9300 2550
	-1   0    0    1   
$EndComp
$Comp
L Device:R R4
U 1 1 5DAE9DB5
P 9300 2250
F 0 "R4" H 9230 2204 50  0000 R CNN
F 1 "1K" H 9230 2295 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9230 2250 50  0001 C CNN
F 3 "~" H 9300 2250 50  0001 C CNN
	1    9300 2250
	-1   0    0    1   
$EndComp
$Comp
L Device:R R3
U 1 1 5DAE99F2
P 9300 1950
F 0 "R3" H 9230 1904 50  0000 R CNN
F 1 "1K" H 9230 1995 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9230 1950 50  0001 C CNN
F 3 "~" H 9300 1950 50  0001 C CNN
	1    9300 1950
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 5DAE9740
P 9300 1650
F 0 "R2" H 9230 1604 50  0000 R CNN
F 1 "1K" H 9230 1695 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9230 1650 50  0001 C CNN
F 3 "~" H 9300 1650 50  0001 C CNN
	1    9300 1650
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 5DAE17E6
P 9300 1350
F 0 "R1" H 9230 1304 50  0000 R CNN
F 1 "1K" H 9230 1395 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9230 1350 50  0001 C CNN
F 3 "~" H 9300 1350 50  0001 C CNN
	1    9300 1350
	-1   0    0    1   
$EndComp
$Comp
L Device:C C1
U 1 1 5DAF5175
P 8400 2150
F 0 "C1" H 8515 2196 50  0000 L CNN
F 1 "2.2uF" H 8515 2105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8438 2000 50  0001 C CNN
F 3 "~" H 8400 2150 50  0001 C CNN
	1    8400 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR02
U 1 1 5DAF5D9B
P 8400 2300
F 0 "#PWR02" H 8400 2050 50  0001 C CNN
F 1 "GNDD" H 8404 2145 50  0000 C CNN
F 2 "" H 8400 2300 50  0001 C CNN
F 3 "" H 8400 2300 50  0001 C CNN
	1    8400 2300
	1    0    0    -1  
$EndComp
Text Label 5800 1900 0    50   ~ 0
GPI34_BUT1_MODE
Connection ~ 8400 2000
Wire Wire Line
	8400 2000 8550 2000
Wire Wire Line
	6950 2100 7050 2100
Wire Wire Line
	7050 2100 7050 2350
Wire Wire Line
	7050 2000 7050 2050
Wire Wire Line
	7050 1600 6950 1600
Wire Wire Line
	7050 1350 7050 1600
Wire Wire Line
	7050 1700 6950 1700
Wire Wire Line
	7050 1650 7050 1700
Wire Wire Line
	7050 2000 6950 2000
Wire Wire Line
	7100 2350 7100 2600
Wire Wire Line
	7050 2350 7100 2350
Wire Wire Line
	7100 2050 7100 2300
Wire Wire Line
	7050 2050 7100 2050
Wire Wire Line
	7100 1900 7100 2000
Wire Wire Line
	7100 1350 7050 1350
Wire Wire Line
	7100 1100 7100 1350
Wire Wire Line
	7100 1650 7050 1650
Wire Wire Line
	7100 1400 7100 1650
Wire Wire Line
	7100 1800 6950 1800
Wire Wire Line
	7100 1700 7100 1800
Wire Wire Line
	7100 1900 6950 1900
Connection ~ 7200 2600
$Comp
L power:GNDD #PWR0102
U 1 1 5DB0A0A9
P 7200 2600
F 0 "#PWR0102" H 7200 2350 50  0001 C CNN
F 1 "GNDD" H 7204 2445 50  0000 C CNN
F 2 "" H 7200 2600 50  0001 C CNN
F 3 "" H 7200 2600 50  0001 C CNN
	1    7200 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 2600 7200 2600
Connection ~ 7200 2300
Wire Wire Line
	7100 2300 7200 2300
Connection ~ 7200 2000
Wire Wire Line
	7100 2000 7200 2000
Wire Wire Line
	7200 1100 7100 1100
Connection ~ 7200 1400
Wire Wire Line
	7200 1400 7100 1400
Connection ~ 7200 1700
Wire Wire Line
	7200 1700 7100 1700
$Comp
L Device:R R10
U 1 1 5DB0A0B9
P 7200 2450
F 0 "R10" H 7130 2404 50  0000 R CNN
F 1 "1K" H 7130 2495 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7130 2450 50  0001 C CNN
F 3 "~" H 7200 2450 50  0001 C CNN
	1    7200 2450
	-1   0    0    1   
$EndComp
$Comp
L Device:R R9
U 1 1 5DB0A0BF
P 7200 2150
F 0 "R9" H 7130 2104 50  0000 R CNN
F 1 "1K" H 7130 2195 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7130 2150 50  0001 C CNN
F 3 "~" H 7200 2150 50  0001 C CNN
	1    7200 2150
	-1   0    0    1   
$EndComp
$Comp
L Device:R R8
U 1 1 5DB0A0C5
P 7200 1850
F 0 "R8" H 7130 1804 50  0000 R CNN
F 1 "1K" H 7130 1895 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7130 1850 50  0001 C CNN
F 3 "~" H 7200 1850 50  0001 C CNN
	1    7200 1850
	-1   0    0    1   
$EndComp
$Comp
L Device:R R7
U 1 1 5DB0A0CB
P 7200 1550
F 0 "R7" H 7130 1504 50  0000 R CNN
F 1 "1K" H 7130 1595 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7130 1550 50  0001 C CNN
F 3 "~" H 7200 1550 50  0001 C CNN
	1    7200 1550
	-1   0    0    1   
$EndComp
$Comp
L Device:R R6
U 1 1 5DB0A0D1
P 7200 1250
F 0 "R6" H 7130 1204 50  0000 R CNN
F 1 "1K" H 7130 1295 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7130 1250 50  0001 C CNN
F 3 "~" H 7200 1250 50  0001 C CNN
	1    7200 1250
	-1   0    0    1   
$EndComp
$Comp
L Device:C C2
U 1 1 5DB0A0D7
P 6300 2050
F 0 "C2" H 6415 2096 50  0000 L CNN
F 1 "2.2uF" H 6415 2005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6338 1900 50  0001 C CNN
F 3 "~" H 6300 2050 50  0001 C CNN
	1    6300 2050
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0103
U 1 1 5DB0A0DD
P 6300 2200
F 0 "#PWR0103" H 6300 1950 50  0001 C CNN
F 1 "GNDD" H 6304 2045 50  0000 C CNN
F 2 "" H 6300 2200 50  0001 C CNN
F 3 "" H 6300 2200 50  0001 C CNN
	1    6300 2200
	1    0    0    -1  
$EndComp
Text Label 7850 2000 0    50   ~ 0
GPI39_COLOR
Connection ~ 6300 1900
Wire Wire Line
	6300 1900 6450 1900
$Comp
L Device:R_POT RV2
U 1 1 5DB1EC9A
P 8550 1100
F 0 "RV2" H 8480 1054 50  0000 R CNN
F 1 "R_POT" H 8480 1145 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_TT_P0915N" H 8550 1100 50  0001 C CNN
F 3 "~" H 8550 1100 50  0001 C CNN
	1    8550 1100
	-1   0    0    1   
$EndComp
$Comp
L power:GNDD #PWR0104
U 1 1 5DB22F79
P 8550 1250
F 0 "#PWR0104" H 8550 1000 50  0001 C CNN
F 1 "GNDD" H 8554 1095 50  0000 C CNN
F 2 "" H 8550 1250 50  0001 C CNN
F 3 "" H 8550 1250 50  0001 C CNN
	1    8550 1250
	1    0    0    -1  
$EndComp
Text Label 7800 1100 0    50   ~ 0
GPIO33_BRIGHT
$Comp
L Device:R_POT RV1
U 1 1 5DB2A214
P 6450 900
F 0 "RV1" H 6380 854 50  0000 R CNN
F 1 "R_POT" H 6380 945 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_TT_P0915N" H 6450 900 50  0001 C CNN
F 3 "~" H 6450 900 50  0001 C CNN
	1    6450 900 
	-1   0    0    1   
$EndComp
$Comp
L power:GNDD #PWR0106
U 1 1 5DB2A21A
P 6450 1050
F 0 "#PWR0106" H 6450 800 50  0001 C CNN
F 1 "GNDD" H 6454 895 50  0000 C CNN
F 2 "" H 6450 1050 50  0001 C CNN
F 3 "" H 6450 1050 50  0001 C CNN
	1    6450 1050
	1    0    0    -1  
$EndComp
Text Label 5750 900  0    50   ~ 0
GPI35_SPEED
$Comp
L power:GNDD #PWR0109
U 1 1 5DB2EFD5
P 1850 2050
F 0 "#PWR0109" H 1850 1800 50  0001 C CNN
F 1 "GNDD" H 1854 1895 50  0000 C CNN
F 2 "" H 1850 2050 50  0001 C CNN
F 3 "" H 1850 2050 50  0001 C CNN
	1    1850 2050
	0    1    1    0   
$EndComp
$Comp
L LED:WS2812B D1
U 1 1 5DB39DEB
P 1600 5150
F 0 "D1" H 1400 5400 50  0000 R CNN
F 1 "WS2812B" H 1150 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 1650 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 1700 4775 50  0001 L TNN
	1    1600 5150
	1    0    0    -1  
$EndComp
Text Label 650  5150 0    50   ~ 0
GPIO32_PREVIEW
$Comp
L LED:WS2812B D2
U 1 1 5DB3D90F
P 2200 5150
F 0 "D2" H 2000 5400 50  0000 R CNN
F 1 "WS2812B" H 1750 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 2250 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 2300 4775 50  0001 L TNN
	1    2200 5150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D3
U 1 1 5DB3E16D
P 2800 5150
F 0 "D3" H 2600 5400 50  0000 R CNN
F 1 "WS2812B" H 2350 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 2850 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 2900 4775 50  0001 L TNN
	1    2800 5150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D4
U 1 1 5DB3EA19
P 3400 5150
F 0 "D4" H 3200 5400 50  0000 R CNN
F 1 "WS2812B" H 2950 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 3450 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 3500 4775 50  0001 L TNN
	1    3400 5150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D5
U 1 1 5DB46580
P 4000 5150
F 0 "D5" H 3800 5400 50  0000 R CNN
F 1 "WS2812B" H 3550 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 4050 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 4100 4775 50  0001 L TNN
	1    4000 5150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D6
U 1 1 5DB46E05
P 4600 5150
F 0 "D6" H 4400 5400 50  0000 R CNN
F 1 "WS2812B" H 4150 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 4650 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 4700 4775 50  0001 L TNN
	1    4600 5150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D7
U 1 1 5DB47885
P 5200 5150
F 0 "D7" H 5000 5400 50  0000 R CNN
F 1 "WS2812B" H 4750 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 5250 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 5300 4775 50  0001 L TNN
	1    5200 5150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D8
U 1 1 5DB481A6
P 5800 5150
F 0 "D8" H 5600 5400 50  0000 R CNN
F 1 "WS2812B" H 5350 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 5850 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 5900 4775 50  0001 L TNN
	1    5800 5150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D9
U 1 1 5DB65B7B
P 6400 5150
F 0 "D9" H 6200 5400 50  0000 R CNN
F 1 "WS2812B" H 5950 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 6450 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 6500 4775 50  0001 L TNN
	1    6400 5150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D10
U 1 1 5DB65B81
P 7000 5150
F 0 "D10" H 6800 5400 50  0000 R CNN
F 1 "WS2812B" H 6550 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 7050 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 7100 4775 50  0001 L TNN
	1    7000 5150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D11
U 1 1 5DB65B87
P 7600 5150
F 0 "D11" H 7400 5400 50  0000 R CNN
F 1 "WS2812B" H 7150 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 7650 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 7700 4775 50  0001 L TNN
	1    7600 5150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D12
U 1 1 5DB65B8D
P 8200 5150
F 0 "D12" H 8000 5400 50  0000 R CNN
F 1 "WS2812B" H 7750 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 8250 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 8300 4775 50  0001 L TNN
	1    8200 5150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D13
U 1 1 5DB65B93
P 8800 5150
F 0 "D13" H 8600 5400 50  0000 R CNN
F 1 "WS2812B" H 8350 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 8850 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 8900 4775 50  0001 L TNN
	1    8800 5150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D14
U 1 1 5DB65B99
P 9400 5150
F 0 "D14" H 9200 5400 50  0000 R CNN
F 1 "WS2812B" H 8950 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 9450 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 9500 4775 50  0001 L TNN
	1    9400 5150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D15
U 1 1 5DB65B9F
P 10000 5150
F 0 "D15" H 9800 5400 50  0000 R CNN
F 1 "WS2812B" H 9550 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 10050 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 10100 4775 50  0001 L TNN
	1    10000 5150
	1    0    0    -1  
$EndComp
$Comp
L LED:WS2812B D16
U 1 1 5DB65BA5
P 10600 5150
F 0 "D16" H 10400 5400 50  0000 R CNN
F 1 "WS2812B" H 10150 4900 50  0000 L CNN
F 2 "LED_SMD:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm" H 10650 4850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/datasheets/WS2812B.pdf" H 10700 4775 50  0001 L TNN
	1    10600 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 5450 2200 5450
Wire Wire Line
	2200 5450 2800 5450
Connection ~ 2200 5450
Wire Wire Line
	2800 5450 3400 5450
Wire Wire Line
	3400 5450 4000 5450
Connection ~ 2800 5450
Connection ~ 3400 5450
Wire Wire Line
	4600 5450 4000 5450
Connection ~ 4000 5450
Connection ~ 4600 5450
Wire Wire Line
	4600 5450 5200 5450
Wire Wire Line
	5800 5450 5200 5450
Connection ~ 5200 5450
Wire Wire Line
	10600 5450 10000 5450
Connection ~ 5800 5450
Connection ~ 6400 5450
Wire Wire Line
	6400 5450 5800 5450
Connection ~ 7000 5450
Wire Wire Line
	7000 5450 6400 5450
Connection ~ 7600 5450
Wire Wire Line
	7600 5450 7000 5450
Connection ~ 8200 5450
Wire Wire Line
	8200 5450 7600 5450
Connection ~ 8800 5450
Wire Wire Line
	8800 5450 8200 5450
Connection ~ 9400 5450
Wire Wire Line
	9400 5450 8800 5450
Connection ~ 10000 5450
Wire Wire Line
	10000 5450 9400 5450
Connection ~ 2200 4850
Wire Wire Line
	2200 4850 1600 4850
Connection ~ 2800 4850
Wire Wire Line
	2800 4850 2200 4850
Connection ~ 3400 4850
Wire Wire Line
	3400 4850 2800 4850
Connection ~ 4000 4850
Wire Wire Line
	4000 4850 3400 4850
Connection ~ 4600 4850
Wire Wire Line
	4600 4850 4000 4850
Connection ~ 5200 4850
Wire Wire Line
	5200 4850 4600 4850
Connection ~ 5800 4850
Wire Wire Line
	5800 4850 5200 4850
Connection ~ 6400 4850
Wire Wire Line
	6400 4850 5800 4850
Connection ~ 7000 4850
Wire Wire Line
	7000 4850 6400 4850
Connection ~ 7600 4850
Wire Wire Line
	7600 4850 7000 4850
Connection ~ 8200 4850
Wire Wire Line
	8200 4850 7600 4850
Connection ~ 8800 4850
Wire Wire Line
	8800 4850 8200 4850
Connection ~ 9400 4850
Wire Wire Line
	9400 4850 8800 4850
Connection ~ 10000 4850
Wire Wire Line
	10000 4850 9400 4850
$Comp
L power:GNDD #PWR0110
U 1 1 5DB77A17
P 5800 5450
F 0 "#PWR0110" H 5800 5200 50  0001 C CNN
F 1 "GNDD" H 5804 5295 50  0000 C CNN
F 2 "" H 5800 5450 50  0001 C CNN
F 3 "" H 5800 5450 50  0001 C CNN
	1    5800 5450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0111
U 1 1 5DB77FD4
P 5800 4850
F 0 "#PWR0111" H 5800 4700 50  0001 C CNN
F 1 "+5V" H 5815 5023 50  0000 C CNN
F 2 "" H 5800 4850 50  0001 C CNN
F 3 "" H 5800 4850 50  0001 C CNN
	1    5800 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 4850 10600 4850
$Comp
L YonaSymbols:RM106772BCB S1
U 1 1 5DBAB703
P 6750 1800
F 0 "S1" H 6700 2221 50  0000 C CNN
F 1 "RM106772BCB" H 6700 2130 50  0000 C CNN
F 2 "YonaFootprints:RM106772BCB" H 6750 1800 50  0001 L BNN
F 3 "" H 6750 1800 50  0001 L BNN
F 4 "Unavailable" H 6750 1800 50  0001 L BNN "Field4"
F 5 "C&K" H 6750 1800 50  0001 L BNN "Field5"
F 6 "None" H 6750 1800 50  0001 L BNN "Field6"
F 7 "None" H 6750 1800 50  0001 L BNN "Field7"
F 8 "RM106772BCB" H 6750 1800 50  0001 L BNN "Field8"
	1    6750 1800
	1    0    0    -1  
$EndComp
$Comp
L YonaSymbols:RM106772BCB S2
U 1 1 5DBB2E49
P 8850 1900
F 0 "S2" H 8800 2321 50  0000 C CNN
F 1 "RM106772BCB" H 8800 2230 50  0000 C CNN
F 2 "YonaFootprints:RM106772BCB" H 8850 1900 50  0001 L BNN
F 3 "" H 8850 1900 50  0001 L BNN
F 4 "Unavailable" H 8850 1900 50  0001 L BNN "Field4"
F 5 "C&K" H 8850 1900 50  0001 L BNN "Field5"
F 6 "None" H 8850 1900 50  0001 L BNN "Field6"
F 7 "None" H 8850 1900 50  0001 L BNN "Field7"
F 8 "RM106772BCB" H 8850 1900 50  0001 L BNN "Field8"
	1    8850 1900
	1    0    0    -1  
$EndComp
Text Label 2150 2350 2    39   ~ 0
GPIO1/U0TXD
Text Label 2150 2450 2    39   ~ 0
GPIO2/HS2_DATA0
Text Label 2150 2550 2    39   ~ 0
GPIO3/U0RXD
Text Label 2150 2650 2    39   ~ 0
GPIO4/U1TXD
Text Label 2150 2750 2    39   ~ 0
GPIO5/SPI_CS
Text Label 4350 2750 0    39   ~ 0
GPIO13/I2C-SDA
Text Label 4350 2650 0    39   ~ 0
GPIO14/HS2_CLK
Text Label 4350 2550 0    39   ~ 0
GPIO15/HS2_CMD
Text Label 4350 2450 0    39   ~ 0
GPIO16/I2C-SCL
Text Label 4350 2350 0    39   ~ 0
GPIO32_PREVIEW
Text Label 4350 2250 0    39   ~ 0
GPIO33_BRIGHT
Text Label 4350 2150 0    39   ~ 0
GPI34_BUT1_MODE
Text Label 4350 2050 0    39   ~ 0
GPI35_SPEED
Text Label 4350 1950 0    39   ~ 0
GPI36/U1RXD
Text Label 4350 1850 0    39   ~ 0
GPI39_COLOR
$Comp
L AndyCabinets-rescue:+5V-ESP32-PoE-ISO_Rev_C #PWR0108
U 1 1 5E0451F0
P 1850 1850
F 0 "#PWR0108" H 1850 1700 50  0001 C CNN
F 1 "+5V" V 1865 1978 50  0000 L CNN
F 2 "" H 1850 1850 60  0000 C CNN
F 3 "" H 1850 1850 60  0000 C CNN
	1    1850 1850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2350 2350 1050 2350
Wire Wire Line
	1050 2450 2350 2450
Wire Wire Line
	2350 2550 1050 2550
Wire Wire Line
	1050 2650 2350 2650
Wire Wire Line
	2350 2750 1050 2750
Wire Wire Line
	5050 2750 4150 2750
Wire Wire Line
	4150 2650 5050 2650
Wire Wire Line
	5050 2550 4150 2550
Wire Wire Line
	4150 1950 5050 1950
Wire Wire Line
	4150 2450 5050 2450
Wire Wire Line
	2350 2050 1850 2050
Wire Wire Line
	2350 1850 1850 1850
Text Label 2150 2150 2    39   ~ 0
ESP_EN
Wire Wire Line
	1050 2150 2350 2150
$Comp
L AndyCabinets-rescue:+3.3V-ESP32-PoE-ISO_Rev_C #PWR0112
U 1 1 5E045209
P 1850 1950
F 0 "#PWR0112" H 1850 1800 50  0001 C CNN
F 1 "+3.3V" V 1865 2078 50  0000 L CNN
F 2 "" H 1850 1950 60  0000 C CNN
F 3 "" H 1850 1950 60  0000 C CNN
	1    1850 1950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1850 1950 2350 1950
Text Label 2150 2250 2    39   ~ 0
GPIO0
Wire Wire Line
	1050 2250 2350 2250
$Comp
L AndyCabinets-rescue:CON10-ESP32-PoE-ISO_Rev_C EXT1
U 1 1 5E045212
P 2450 2250
F 0 "EXT1" H 2400 2800 60  0000 C CNN
F 1 "NS(HN1x10)" H 2550 1600 60  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x10_P2.54mm_Vertical_SMD_Pin1Left" H 2375 2600 60  0001 C CNN
F 3 "" H 2375 2600 60  0000 C CNN
	1    2450 2250
	-1   0    0    -1  
$EndComp
$Comp
L AndyCabinets-rescue:CON10-ESP32-PoE-ISO_Rev_C EXT2
U 1 1 5E045218
P 4050 2250
F 0 "EXT2" H 4000 2800 60  0000 C CNN
F 1 "NS(HN1x10)" H 4150 1600 60  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x10_P2.54mm_Vertical_SMD_Pin1Left" H 3975 2600 60  0001 C CNN
F 3 "" H 3975 2600 60  0000 C CNN
	1    4050 2250
	1    0    0    -1  
$EndComp
NoConn ~ 5050 2750
NoConn ~ 5050 2650
NoConn ~ 5050 2550
NoConn ~ 5050 2450
NoConn ~ 1050 2750
NoConn ~ 1050 2650
NoConn ~ 1050 2550
NoConn ~ 1050 2450
NoConn ~ 1050 2350
NoConn ~ 1050 2250
NoConn ~ 1050 2150
NoConn ~ 10900 5150
NoConn ~ 5050 1950
$Comp
L Device:C C3
U 1 1 5E09A3EA
P 1600 4200
F 0 "C3" H 1715 4246 50  0000 L CNN
F 1 "100nF" H 1715 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1638 4050 50  0001 C CNN
F 3 "~" H 1600 4200 50  0001 C CNN
	1    1600 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR0113
U 1 1 5E09ADE3
P 1600 4350
F 0 "#PWR0113" H 1600 4100 50  0001 C CNN
F 1 "GNDD" H 1604 4195 50  0000 C CNN
F 2 "" H 1600 4350 50  0001 C CNN
F 3 "" H 1600 4350 50  0001 C CNN
	1    1600 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0114
U 1 1 5E09AE3C
P 1600 4050
F 0 "#PWR0114" H 1600 3900 50  0001 C CNN
F 1 "+5V" H 1615 4223 50  0000 C CNN
F 2 "" H 1600 4050 50  0001 C CNN
F 3 "" H 1600 4050 50  0001 C CNN
	1    1600 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5E16E55D
P 2200 4200
F 0 "C4" H 2315 4246 50  0000 L CNN
F 1 "100nF" H 2315 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2238 4050 50  0001 C CNN
F 3 "~" H 2200 4200 50  0001 C CNN
	1    2200 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR019
U 1 1 5E16E563
P 2200 4350
F 0 "#PWR019" H 2200 4100 50  0001 C CNN
F 1 "GNDD" H 2204 4195 50  0000 C CNN
F 2 "" H 2200 4350 50  0001 C CNN
F 3 "" H 2200 4350 50  0001 C CNN
	1    2200 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR04
U 1 1 5E16E569
P 2200 4050
F 0 "#PWR04" H 2200 3900 50  0001 C CNN
F 1 "+5V" H 2215 4223 50  0000 C CNN
F 2 "" H 2200 4050 50  0001 C CNN
F 3 "" H 2200 4050 50  0001 C CNN
	1    2200 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5E174538
P 2800 4200
F 0 "C5" H 2915 4246 50  0000 L CNN
F 1 "100nF" H 2915 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2838 4050 50  0001 C CNN
F 3 "~" H 2800 4200 50  0001 C CNN
	1    2800 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR020
U 1 1 5E17453E
P 2800 4350
F 0 "#PWR020" H 2800 4100 50  0001 C CNN
F 1 "GNDD" H 2804 4195 50  0000 C CNN
F 2 "" H 2800 4350 50  0001 C CNN
F 3 "" H 2800 4350 50  0001 C CNN
	1    2800 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR05
U 1 1 5E174544
P 2800 4050
F 0 "#PWR05" H 2800 3900 50  0001 C CNN
F 1 "+5V" H 2815 4223 50  0000 C CNN
F 2 "" H 2800 4050 50  0001 C CNN
F 3 "" H 2800 4050 50  0001 C CNN
	1    2800 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5E17A5C4
P 3400 4200
F 0 "C6" H 3515 4246 50  0000 L CNN
F 1 "100nF" H 3515 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3438 4050 50  0001 C CNN
F 3 "~" H 3400 4200 50  0001 C CNN
	1    3400 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR021
U 1 1 5E17A5CA
P 3400 4350
F 0 "#PWR021" H 3400 4100 50  0001 C CNN
F 1 "GNDD" H 3404 4195 50  0000 C CNN
F 2 "" H 3400 4350 50  0001 C CNN
F 3 "" H 3400 4350 50  0001 C CNN
	1    3400 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR06
U 1 1 5E17A5D0
P 3400 4050
F 0 "#PWR06" H 3400 3900 50  0001 C CNN
F 1 "+5V" H 3415 4223 50  0000 C CNN
F 2 "" H 3400 4050 50  0001 C CNN
F 3 "" H 3400 4050 50  0001 C CNN
	1    3400 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5E1AC0ED
P 4000 4200
F 0 "C7" H 4115 4246 50  0000 L CNN
F 1 "100nF" H 4115 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4038 4050 50  0001 C CNN
F 3 "~" H 4000 4200 50  0001 C CNN
	1    4000 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR022
U 1 1 5E1AC0F3
P 4000 4350
F 0 "#PWR022" H 4000 4100 50  0001 C CNN
F 1 "GNDD" H 4004 4195 50  0000 C CNN
F 2 "" H 4000 4350 50  0001 C CNN
F 3 "" H 4000 4350 50  0001 C CNN
	1    4000 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR07
U 1 1 5E1AC0F9
P 4000 4050
F 0 "#PWR07" H 4000 3900 50  0001 C CNN
F 1 "+5V" H 4015 4223 50  0000 C CNN
F 2 "" H 4000 4050 50  0001 C CNN
F 3 "" H 4000 4050 50  0001 C CNN
	1    4000 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 5E1AC0FF
P 4600 4200
F 0 "C8" H 4715 4246 50  0000 L CNN
F 1 "100nF" H 4715 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4638 4050 50  0001 C CNN
F 3 "~" H 4600 4200 50  0001 C CNN
	1    4600 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR023
U 1 1 5E1AC105
P 4600 4350
F 0 "#PWR023" H 4600 4100 50  0001 C CNN
F 1 "GNDD" H 4604 4195 50  0000 C CNN
F 2 "" H 4600 4350 50  0001 C CNN
F 3 "" H 4600 4350 50  0001 C CNN
	1    4600 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR08
U 1 1 5E1AC10B
P 4600 4050
F 0 "#PWR08" H 4600 3900 50  0001 C CNN
F 1 "+5V" H 4615 4223 50  0000 C CNN
F 2 "" H 4600 4050 50  0001 C CNN
F 3 "" H 4600 4050 50  0001 C CNN
	1    4600 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 5E1AC111
P 5200 4200
F 0 "C9" H 5315 4246 50  0000 L CNN
F 1 "100nF" H 5315 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5238 4050 50  0001 C CNN
F 3 "~" H 5200 4200 50  0001 C CNN
	1    5200 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR024
U 1 1 5E1AC117
P 5200 4350
F 0 "#PWR024" H 5200 4100 50  0001 C CNN
F 1 "GNDD" H 5204 4195 50  0000 C CNN
F 2 "" H 5200 4350 50  0001 C CNN
F 3 "" H 5200 4350 50  0001 C CNN
	1    5200 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR09
U 1 1 5E1AC11D
P 5200 4050
F 0 "#PWR09" H 5200 3900 50  0001 C CNN
F 1 "+5V" H 5215 4223 50  0000 C CNN
F 2 "" H 5200 4050 50  0001 C CNN
F 3 "" H 5200 4050 50  0001 C CNN
	1    5200 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 5E1AC123
P 5800 4200
F 0 "C10" H 5915 4246 50  0000 L CNN
F 1 "100nF" H 5915 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5838 4050 50  0001 C CNN
F 3 "~" H 5800 4200 50  0001 C CNN
	1    5800 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR025
U 1 1 5E1AC129
P 5800 4350
F 0 "#PWR025" H 5800 4100 50  0001 C CNN
F 1 "GNDD" H 5804 4195 50  0000 C CNN
F 2 "" H 5800 4350 50  0001 C CNN
F 3 "" H 5800 4350 50  0001 C CNN
	1    5800 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR010
U 1 1 5E1AC12F
P 5800 4050
F 0 "#PWR010" H 5800 3900 50  0001 C CNN
F 1 "+5V" H 5815 4223 50  0000 C CNN
F 2 "" H 5800 4050 50  0001 C CNN
F 3 "" H 5800 4050 50  0001 C CNN
	1    5800 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 5E1EC94E
P 6400 4200
F 0 "C11" H 6515 4246 50  0000 L CNN
F 1 "100nF" H 6515 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6438 4050 50  0001 C CNN
F 3 "~" H 6400 4200 50  0001 C CNN
	1    6400 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR026
U 1 1 5E1EC954
P 6400 4350
F 0 "#PWR026" H 6400 4100 50  0001 C CNN
F 1 "GNDD" H 6404 4195 50  0000 C CNN
F 2 "" H 6400 4350 50  0001 C CNN
F 3 "" H 6400 4350 50  0001 C CNN
	1    6400 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR011
U 1 1 5E1EC95A
P 6400 4050
F 0 "#PWR011" H 6400 3900 50  0001 C CNN
F 1 "+5V" H 6415 4223 50  0000 C CNN
F 2 "" H 6400 4050 50  0001 C CNN
F 3 "" H 6400 4050 50  0001 C CNN
	1    6400 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 5E1EC960
P 7000 4200
F 0 "C12" H 7115 4246 50  0000 L CNN
F 1 "100nF" H 7115 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7038 4050 50  0001 C CNN
F 3 "~" H 7000 4200 50  0001 C CNN
	1    7000 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR027
U 1 1 5E1EC966
P 7000 4350
F 0 "#PWR027" H 7000 4100 50  0001 C CNN
F 1 "GNDD" H 7004 4195 50  0000 C CNN
F 2 "" H 7000 4350 50  0001 C CNN
F 3 "" H 7000 4350 50  0001 C CNN
	1    7000 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR012
U 1 1 5E1EC96C
P 7000 4050
F 0 "#PWR012" H 7000 3900 50  0001 C CNN
F 1 "+5V" H 7015 4223 50  0000 C CNN
F 2 "" H 7000 4050 50  0001 C CNN
F 3 "" H 7000 4050 50  0001 C CNN
	1    7000 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C13
U 1 1 5E1EC972
P 7600 4200
F 0 "C13" H 7715 4246 50  0000 L CNN
F 1 "100nF" H 7715 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7638 4050 50  0001 C CNN
F 3 "~" H 7600 4200 50  0001 C CNN
	1    7600 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR028
U 1 1 5E1EC978
P 7600 4350
F 0 "#PWR028" H 7600 4100 50  0001 C CNN
F 1 "GNDD" H 7604 4195 50  0000 C CNN
F 2 "" H 7600 4350 50  0001 C CNN
F 3 "" H 7600 4350 50  0001 C CNN
	1    7600 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR013
U 1 1 5E1EC97E
P 7600 4050
F 0 "#PWR013" H 7600 3900 50  0001 C CNN
F 1 "+5V" H 7615 4223 50  0000 C CNN
F 2 "" H 7600 4050 50  0001 C CNN
F 3 "" H 7600 4050 50  0001 C CNN
	1    7600 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C14
U 1 1 5E1EC984
P 8200 4200
F 0 "C14" H 8315 4246 50  0000 L CNN
F 1 "100nF" H 8315 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8238 4050 50  0001 C CNN
F 3 "~" H 8200 4200 50  0001 C CNN
	1    8200 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR029
U 1 1 5E1EC98A
P 8200 4350
F 0 "#PWR029" H 8200 4100 50  0001 C CNN
F 1 "GNDD" H 8204 4195 50  0000 C CNN
F 2 "" H 8200 4350 50  0001 C CNN
F 3 "" H 8200 4350 50  0001 C CNN
	1    8200 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR014
U 1 1 5E1EC990
P 8200 4050
F 0 "#PWR014" H 8200 3900 50  0001 C CNN
F 1 "+5V" H 8215 4223 50  0000 C CNN
F 2 "" H 8200 4050 50  0001 C CNN
F 3 "" H 8200 4050 50  0001 C CNN
	1    8200 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C15
U 1 1 5E1EC996
P 8800 4200
F 0 "C15" H 8915 4246 50  0000 L CNN
F 1 "100nF" H 8915 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8838 4050 50  0001 C CNN
F 3 "~" H 8800 4200 50  0001 C CNN
	1    8800 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR030
U 1 1 5E1EC99C
P 8800 4350
F 0 "#PWR030" H 8800 4100 50  0001 C CNN
F 1 "GNDD" H 8804 4195 50  0000 C CNN
F 2 "" H 8800 4350 50  0001 C CNN
F 3 "" H 8800 4350 50  0001 C CNN
	1    8800 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR015
U 1 1 5E1EC9A2
P 8800 4050
F 0 "#PWR015" H 8800 3900 50  0001 C CNN
F 1 "+5V" H 8815 4223 50  0000 C CNN
F 2 "" H 8800 4050 50  0001 C CNN
F 3 "" H 8800 4050 50  0001 C CNN
	1    8800 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C16
U 1 1 5E1EC9A8
P 9400 4200
F 0 "C16" H 9515 4246 50  0000 L CNN
F 1 "100nF" H 9515 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9438 4050 50  0001 C CNN
F 3 "~" H 9400 4200 50  0001 C CNN
	1    9400 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR031
U 1 1 5E1EC9AE
P 9400 4350
F 0 "#PWR031" H 9400 4100 50  0001 C CNN
F 1 "GNDD" H 9404 4195 50  0000 C CNN
F 2 "" H 9400 4350 50  0001 C CNN
F 3 "" H 9400 4350 50  0001 C CNN
	1    9400 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR016
U 1 1 5E1EC9B4
P 9400 4050
F 0 "#PWR016" H 9400 3900 50  0001 C CNN
F 1 "+5V" H 9415 4223 50  0000 C CNN
F 2 "" H 9400 4050 50  0001 C CNN
F 3 "" H 9400 4050 50  0001 C CNN
	1    9400 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C17
U 1 1 5E1EC9BA
P 10000 4200
F 0 "C17" H 10115 4246 50  0000 L CNN
F 1 "100nF" H 10115 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10038 4050 50  0001 C CNN
F 3 "~" H 10000 4200 50  0001 C CNN
	1    10000 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR032
U 1 1 5E1EC9C0
P 10000 4350
F 0 "#PWR032" H 10000 4100 50  0001 C CNN
F 1 "GNDD" H 10004 4195 50  0000 C CNN
F 2 "" H 10000 4350 50  0001 C CNN
F 3 "" H 10000 4350 50  0001 C CNN
	1    10000 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR017
U 1 1 5E1EC9C6
P 10000 4050
F 0 "#PWR017" H 10000 3900 50  0001 C CNN
F 1 "+5V" H 10015 4223 50  0000 C CNN
F 2 "" H 10000 4050 50  0001 C CNN
F 3 "" H 10000 4050 50  0001 C CNN
	1    10000 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C18
U 1 1 5E1EC9CC
P 10600 4200
F 0 "C18" H 10715 4246 50  0000 L CNN
F 1 "100nF" H 10715 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10638 4050 50  0001 C CNN
F 3 "~" H 10600 4200 50  0001 C CNN
	1    10600 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR033
U 1 1 5E1EC9D2
P 10600 4350
F 0 "#PWR033" H 10600 4100 50  0001 C CNN
F 1 "GNDD" H 10604 4195 50  0000 C CNN
F 2 "" H 10600 4350 50  0001 C CNN
F 3 "" H 10600 4350 50  0001 C CNN
	1    10600 4350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR018
U 1 1 5E1EC9D8
P 10600 4050
F 0 "#PWR018" H 10600 3900 50  0001 C CNN
F 1 "+5V" H 10615 4223 50  0000 C CNN
F 2 "" H 10600 4050 50  0001 C CNN
F 3 "" H 10600 4050 50  0001 C CNN
	1    10600 4050
	1    0    0    -1  
$EndComp
$Comp
L AndyCabinets-rescue:+3.3V-ESP32-PoE-ISO_Rev_C #PWR0101
U 1 1 5E0E7FA8
P 8550 950
F 0 "#PWR0101" H 8550 800 50  0001 C CNN
F 1 "+3.3V" H 8565 1078 50  0000 L CNN
F 2 "" H 8550 950 60  0000 C CNN
F 3 "" H 8550 950 60  0000 C CNN
	1    8550 950 
	1    0    0    -1  
$EndComp
$Comp
L AndyCabinets-rescue:+3.3V-ESP32-PoE-ISO_Rev_C #PWR0105
U 1 1 5E0F28C5
P 6450 750
F 0 "#PWR0105" H 6450 600 50  0001 C CNN
F 1 "+3.3V" H 6465 878 50  0000 L CNN
F 2 "" H 6450 750 60  0000 C CNN
F 3 "" H 6450 750 60  0000 C CNN
	1    6450 750 
	1    0    0    -1  
$EndComp
$Comp
L AndyCabinets-rescue:+3.3V-ESP32-PoE-ISO_Rev_C #PWR0107
U 1 1 5E0F39DA
P 7200 1100
F 0 "#PWR0107" H 7200 950 50  0001 C CNN
F 1 "+3.3V" H 7215 1228 50  0000 L CNN
F 2 "" H 7200 1100 60  0000 C CNN
F 3 "" H 7200 1100 60  0000 C CNN
	1    7200 1100
	1    0    0    -1  
$EndComp
Connection ~ 7200 1100
$Comp
L AndyCabinets-rescue:+3.3V-ESP32-PoE-ISO_Rev_C #PWR0115
U 1 1 5E0F46C5
P 9300 1200
F 0 "#PWR0115" H 9300 1050 50  0001 C CNN
F 1 "+3.3V" H 9315 1328 50  0000 L CNN
F 2 "" H 9300 1200 60  0000 C CNN
F 3 "" H 9300 1200 60  0000 C CNN
	1    9300 1200
	1    0    0    -1  
$EndComp
Connection ~ 9300 1200
Wire Wire Line
	7850 2000 8400 2000
Wire Wire Line
	5750 900  6300 900 
Wire Wire Line
	650  5150 1300 5150
Wire Wire Line
	5800 1900 6300 1900
Wire Wire Line
	7800 1100 8400 1100
Wire Wire Line
	4350 1850 4150 1850
Wire Wire Line
	4350 2050 4150 2050
Wire Wire Line
	4150 2150 4350 2150
Wire Wire Line
	4350 2250 4150 2250
Wire Wire Line
	4150 2350 4350 2350
$EndSCHEMATC
