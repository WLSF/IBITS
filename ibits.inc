/*
* --- iBits ---
* Por Willian Luigi
* Atualizado - [15/10/2013]
* Atualizado - [04/11/2013]
*
*/
#if defined _ibits_included
#endinput
#endif
#define _ibits_included
#pragma library ibits

enum IPSI_BITS (<<=1)
{
    bit16 = 2,
    bit8,
    bit4,
    bit2,
    bit1
};

stock partBits(n,inicio,fim) {
    return (n >> inicio) & ~(~0 << (fim - inicio + 1));
}

// 1 bit
#define array_bit1:%0<%1,%2> \
                    %0[(%1 + cellbits) / cellbits][(%1 + cellbits) / cellbits]
#define bit1:%0<%1> \
                    %0[(%1 + cellbits) / cellbits]
#define getBit1(%0,%1) \
                    ( ( %0[%1 / cellbits] >> %1 ) & 0x01 )
stock setBit1(arr[], slot, val)
{
    return val ? (arr[slot / cellbits] ^= ((_:val % 0x02) << slot)) : (arr[slot/cellbits] &= ~(0x01 << slot));
}

// 2 bits
#define bit2:%0<%1> \
                    %0[(%1 + _:bit2) / _:bit2]
#define getBit2(%0,%1) \
                    ( %0[%1 / _:bit2] >> ( %1 << 1 ) ) % 0x04
stock setBit2(arr[], slot, val)
{
    return arr[slot/_:bit2] =  ((arr[slot/_:bit2] & ~(0x03 << (slot << 1)))) | ((_:val % 0x04) << (slot << 1));
}

// 4 bits
#define bit4:%0<%1> \
                    %0[(%1 + _:bit4) / _:bit4]
#define getBit4(%0,%1) \
                    ( %0[%1 / _:bit4] >> ( %1 << 2 ) ) % 0x10
stock setBit4(arr[], slot, val)
{
    return arr[slot/_:bit4] =  ((arr[slot/_:bit4] & ~(0xF << (slot << 2)))) | ((_:val % 0x10) << (slot << 2));
}

// 16 bits
#define bit16:%0<%1> \
                    %0[(%1 + _:bit16) / _:bit16]
#define getBit16(%0,%1) \
                    ( %0[%1 / _:bit16] >> ( %1 << 4 ) ) % (65536)
stock setBit16(arr[], slot, val)
{
    return arr[slot/_:bit16] =  ((arr[slot/_:bit16] & ~(65535 << (slot << 4)))) | ((_:val % 65536) << (slot << 4));
}


//geral bits
#define bit_var%0<%1@%2> \
                    new %0[(%1 + _:%2) / _:%2]
#define bit_var_set:%3(%0,%1,%2) \
                    setBit%3(%0,%1,%2)
#define bit_var_get:%2(%0,%1) \
                    getBit%2(%0,%1)

#define bit_array%0<%1,%2@%3> \
                    new %0[(_:%1)][(_:%2 + _:%3) / _:%3]
#define bit_array_set:%4(%0,%1,%2,%3) \
                    setBit%4(%0[%1],_:%2,%3)

#define bit_array_get:%3(%0,%1,%2) \
                    getBit%3(%0[%1],_:%2)


// funcionalidades

#define size(%0,%1) \
                (sizeof(%0) * _:%1) //Retorna o tamanho da estrutura


stock bool:any(arr[], slot, IPSI_BITS: type) //Verifica se algum bit da sequência está ativo(1)
{
    switch(_:type)
    {
        case bit16: return bool:(getBit16(arr, slot) ^ 0b0) && 1;
        case bit4: return bool:(getBit4(arr, slot) ^ 0b0) && 1;
        case bit2: return bool:(getBit2(arr, slot) ^ 0b0) && 1;
        case bit1: return bool:(getBit1(arr, slot) ^ 0b0) && 1;
        default: return false;
    }
    return false;
}
stock bool:none(arr[], slot, IPSI_BITS: type) //Verifica se nenhum bit da sequência está ativo(1)
{
    switch(_:type)
    {
        case bit16: return bool:(!(getBit16(arr, slot) ^ 0b0)) && 1;
        case bit4: return bool:(!(getBit4(arr, slot) ^ 0b0)) && 1;
        case bit2: return bool:(!(getBit2(arr, slot) ^ 0b0)) && 1;
        case bit1: return bool:(!(getBit1(arr, slot) ^ 0b0)) && 1;
        default: return false;
    }
    return false;
}