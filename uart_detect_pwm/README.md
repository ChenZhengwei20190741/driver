# uart_detect_pwm example

## 说明

本 demo 主要针对于 ESP32S2 上没有MCPWM，而无法测量脉宽问题。
此 demo 主要采用 UART 的波特率检测功能来测量 PWM 的频率和占空比。（代码上，esp32和esp32s2通用）

## 使用方法

将 UART 的 RX（GPIO4） 接到 PWM（GPIO18） 上即可。
输出如下：
```
I (47) boot: ESP-IDF v4.2-dev-1995-g636b964c8-dirty 2nd stage bootloader
I (47) boot: compile time 11:50:44
I (47) boot: chip revision: 0
I (50) boot.esp32s2: SPI Speed      : 80MHz
I (55) boot.esp32s2: SPI Mode       : DIO
I (60) boot.esp32s2: SPI Flash Size : 2MB
I (65) boot: Enabling RNG early entropy source...
I (70) boot: Partition Table:
I (74) boot: ## Label            Usage          Type ST Offset   Length
I (81) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (88) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (96) boot:  2 factory          factory app      00 00 00010000 00100000
I (103) boot: End of partition table
I (108) esp_image: segment 0: paddr=0x00010020 vaddr=0x3f000020 size=0x05998 ( 22936) map
I (121) esp_image: segment 1: paddr=0x000159c0 vaddr=0x3ffbdd30 size=0x01eb0 (  7856) load
I (127) esp_image: segment 2: paddr=0x00017878 vaddr=0x40024000 size=0x00404 (  1028) load
0x40024000: _WindowOverflow4 at /home/chenzhengwei/esp/esp-idf/components/freertos/xtensa/xtensa_vectors.S:1730

I (135) esp_image: segment 3: paddr=0x00017c84 vaddr=0x40024404 size=0x08394 ( 33684) load
I (152) esp_image: segment 4: paddr=0x00020020 vaddr=0x40080020 size=0x15824 ( 88100) map
0x40080020: _stext at ??:?

I (171) esp_image: segment 5: paddr=0x0003584c vaddr=0x4002c798 size=0x01590 (  5520) load
0x4002c798: spimem_flash_ll_set_addr_bitlen at /home/chenzhengwei/esp/esp-idf/components/soc/src/esp32s2/include/hal/spimem_flash_ll.h:345
 (inlined by) spi_flash_hal_configure_host_io_mode at /home/chenzhengwei/esp/esp-idf/components/soc/src/hal/spi_flash_hal_common.inc:82

I (178) boot: Loaded app from partition at offset 0x10000
I (178) boot: Disabling RNG early entropy source...
I (180) cache: Instruction cache        : size 8KB, 4Ways, cache line size 32Byte
I (188) cpu_start: Pro cpu up.
I (192) cpu_start: Application information:
I (196) cpu_start: Project name:     ledc
I (201) cpu_start: App version:      1
I (205) cpu_start: Compile time:     Oct 15 2020 11:50:37
I (212) cpu_start: ELF file SHA256:  6777d4f9ec18031f...
I (218) cpu_start: ESP-IDF:          v4.2-dev-1995-g636b964c8-dirty
I (225) cpu_start: Single core mode
I (229) heap_init: Initializing. RAM available for dynamic allocation:
I (236) heap_init: At 3FFC03C0 len 0003BC40 (239 KiB): DRAM
I (242) heap_init: At 3FFFC000 len 00003A10 (14 KiB): DRAM
I (248) cpu_start: Pro cpu start user code
I (309) spi_flash: detected chip: generic
I (309) spi_flash: flash io: dio
W (309) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (320) cpu_start: Starting scheduler on PRO CPU.
freq: 5000Hz,   duty 0.4999
freq: 5000Hz,   duty 0.4999
freq: 5000Hz,   duty 0.4999
freq: 5000Hz,   duty 0.4999
freq: 5000Hz,   duty 0.4999
freq: 5000Hz,   duty 0.4999
freq: 5000Hz,   duty 0.4999
freq: 5000Hz,   duty 0.4999
freq: 5000Hz,   duty 0.4999
freq: 5000Hz,   duty 0.4999
freq: 5000Hz,   duty 0.4999
freq: 5000Hz,   duty 0.4999

```