// // #include <iostream>

// #include <stdio.h>
// #include <inttypes.h>

// #include "bitboard.h"
// // using namespace std;


// int main(int argc, char *argv[])
// {
//     BitBoard bitboard_a(23, 23);
//     BitBoard bitboard_b(23, 23);

//     uint8_t output;

//     printf("---test---\n");
//     bitboard_a.set(1, 0);
//     output = bitboard_a.get(0, 0);
//     // printf("get()=%" PRIu8 "\n", output);

//     // bitboard_a.clear(0, 0);
//     output = bitboard_a.get(1, 0);
//     // printf("get()=%" PRIu8 "\n", output);

//     // bitboard_a.clear(1, 0);
//     output = bitboard_a.get(1, 0);
//     // printf("get()=%" PRIu8 "\n", output);

//     output = bitboard_b.get(1, 0);
//     printf("get()=%" PRIu8 "\n", output);


//     bitboard_b.set(1, 0);
//     output = bitboard_b.get(1, 0);
//     printf("get()=%" PRIu8 "\n", output);

//     return 0;
// }
