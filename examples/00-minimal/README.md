# 00-minimal

Hi anh em, nay mình sẽ giới thiệu tới anh em một chương trình bare-metal đơn giản nhất được thực hiện trên AK Embedded Base Kit (STM32L151).

## Mục tiêu

Mục đích của chương trình này nhằm chứng minh chip sống và toolchain đang hoạt động:
- Toolchain debug được
- Linker đã đặt vector table đúng addr 0x08000000 (Các bạn có thể xem trong file linker script)
- CPU reset -> đọc được SP và Reset_Handler -> trỏ tới main() được

## File

| File | Vai trò |
|-------|----------|
| `main.c` | Đây là startup code gồm có Vector table, Reset_Handler và main() |
| `stm32l151xx.ld` | Đây là linker script với kích thước Flash là 128KB (0x08000000) và SRAM là 16KB (0x20000000) |
| `Makefile` | File build và flash firmware |

## Build và flash

Build file:

```bash
make
```
Nạp lên kit (dùng ST-Link V2):

```bash
make flash
```

Nạp lên kit (dùng UART):

```bash
make flash dev=/dev/ttyUSB0
```

Xóa file build:

```bash
make clean
```

## Kết quả

<table align="center">
  <tr>
    <td align="center"><img src="../../resources/images/00-minimal/minimal-build-successfully.png" alt="Build successfully" width="1000"/></td>
  </tr>
</table>
<p align="center"><strong><em>Figure 1:</em></strong> Build successfully</p>

Sau khi chạy `make`, toolchain `arm-none-eabi-gcc` biên dịch `main.c` theo `stm32l151xx.ld` và sinh ra file ELF cùng file `.bin` trong thư mục `build_00-minimal-application/`. Lệnh `arm-none-eabi-size` in ra kích thước các section: `.text` chứa vector table + `Reset_Handler` + `main()` rỗng, `.data` và `.bss` đều bằng 0 vì chương trình chưa khai báo biến nào. Không có warning hay error nghĩa là linker đã đặt vector table đúng địa chỉ `0x08000000` và toolchain hoạt động bình thường.

<table align="center">
  <tr>
    <td align="center"><img src="../../resources/images/00-minimal/minimal-build-binary.png" alt="Build binary" width="1000"/></td>
  </tr>
</table>
<p align="center"><strong><em>Figure 2:</em></strong> Nội dung file binary</p>

Dump file `.bin` bằng `xxd` (hoặc `hexdump`) cho thấy 8 byte đầu chính là nội dung vector table tối thiểu mà CPU Cortex-M3 cần khi reset:
- 4 byte đầu (`0x20004000`) là giá trị nạp vào **MSP** (Main Stack Pointer) — bằng `_estack`, tức đỉnh SRAM 16 KB tại `0x20000000 + 0x4000`.
- 4 byte tiếp theo là địa chỉ **Reset_Handler** (bit 0 = 1 do Thumb mode của Cortex-M).

Khi cấp nguồn / reset, CPU đọc 2 word này từ `0x08000000`, nạp SP, rồi nhảy vào `Reset_Handler` → clear `.bss`, copy `.data`, gọi `main()`. Chương trình chạy đúng nghĩa là chip sống và pipeline build → flash → boot đã thông.

## Contact & Support

<p style="font-size: 20px;"><strong>Cao Trong Phuoc</strong> - Software Engineer - Embedded Systems</p>

``` Note
Thank you for visiting this repository.
If you have any questions, suggestions, or feedback about this project or firmware development, feel free to contact me directly.
```

<a href="https://github.com/caotrongphuoc">
  <img src="https://img.shields.io/badge/GitHub-caotrongphuoc-181717?style=for-the-badge&logo=github&logoColor=white"/>
</a>

<a href="https://www.linkedin.com/in/cao-trong-phuoc/">
  <img src="https://img.shields.io/badge/LinkedIn-Cao%20Trong%20Phuoc-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white"/>
</a>
