OUTPUT_ARCH( "riscv" )

ENTRY( _start )

MEMORY
{
  ram   (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 128M
}

PHDRS
{
  text PT_LOAD;
  data PT_LOAD;
  bss PT_LOAD;
}

SECTIONS
{
  .text   : { *(.text.init) *(.text .text.*) }      >ram AT>ram :text
  .rodata : { *(.rodata .rodata.*) }                >ram AT>ram :text
  .data   : { *(.sdata .sdata.*) *(.data .data.*) } >ram AT>ram :data
  .htif   : { . = ALIGN(1024); *(.htif) }           >ram AT>ram :data
  .bss    : { *(.sbss .sbss.*) *(.bss .bss.*) }     >ram AT>ram :bss
}
