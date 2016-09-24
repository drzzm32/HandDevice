uint16_t rgb(uint32_t color) {
    return ( (int) (((color & 0xFF0000) >> 16) / 8.2258) ) << 11 |
           ( (int) (((color & 0x00FF00) >> 8 ) / 4.0476) ) << 5  |
           ( (int) (((color & 0x0000FF)      ) / 8.2258) );
}