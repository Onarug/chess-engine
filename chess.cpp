#include <iostream>

// Define
#define U64 unsigned long long

// Enum board squares
enum
{
    a8,
    b8,
    c8,
    d8,
    e8,
    f8,
    g8,
    h8,
    a7,
    b7,
    c7,
    d7,
    e7,
    f7,
    g7,
    h7,
    a6,
    b6,
    c6,
    d6,
    e6,
    f6,
    g6,
    h6,
    a5,
    b5,
    c5,
    d5,
    e5,
    f5,
    g5,
    h5,
    a4,
    b4,
    c4,
    d4,
    e4,
    f4,
    g4,
    h4,
    a3,
    b3,
    c3,
    d3,
    e3,
    f3,
    g3,
    h3,
    a2,
    b2,
    c2,
    d2,
    e2,
    f2,
    g2,
    h2,
    a1,
    b1,
    c1,
    d1,
    e1,
    f1,
    g1,
    h1
};

/*

'a8', 'b8', 'c8', 'd8', 'e8', 'f8', 'g8', 'h8',
'a7', 'b7', 'c7', 'd7', 'e7', 'f7', 'g7', 'h7',
'a6', 'b6', 'c6', 'd6', 'e6', 'f6', 'g6', 'h6',
'a5', 'b5', 'c5', 'd5', 'e5', 'f5', 'g5', 'h5',
'a4', 'b4', 'c4', 'd4', 'e4', 'f4', 'g4', 'h4',
'a3', 'b3', 'c3', 'd3', 'e3', 'f3', 'g3', 'h3',
'a2', 'b2', 'c2', 'd2', 'e2', 'f2', 'g2', 'h2',
'a1', 'b1', 'c1', 'd1', 'e1', 'f1', 'g1', 'h1',

*/
enum
{
    white,
    black
};

// Bit Macros //
// Get bit
#define get_bit(bitboard, square) (bitboard & (1ULL << square))
// Set bit
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
// Pop bit
#define pop_bit(bitboard, square) (get_bit(bitboard, square) ? bitboard ^= (1ULL << square) : 0)

// pawn attacks table
U64 pawn_attacks[2][64];

// generate pawn attacks
U64 mask_pawn_attacks(int square, int side)
{
    // piece bit board
    U64 bitboard = 0ULL;
    // results attack bitboards
    U64 attacks = 0ULL;

    // set piece on board
    set_bit(bitboard, square);

    // white
    if (!side)
    {

    } else {
    // black

    }

    // return attack map
    return attacks;
}

void getChessSquares()
{
    for (int rank = 8; rank >= 1; rank--)
    {
        std::cout << "'" << "a" << rank << "', ";
        std::cout << "'" << "b" << rank << "', ";
        std::cout << "'" << "c" << rank << "', ";
        std::cout << "'" << "d" << rank << "', ";
        std::cout << "'" << "e" << rank << "', ";
        std::cout << "'" << "f" << rank << "', ";
        std::cout << "'" << "g" << rank << "', ";
        std::cout << "'" << "h" << rank << "', \n";
    }
}
// Print bitboard
void print_bitboard(U64 bitboard)
{

    std::cout << "\n";

    // loop over the board ranks
    for (int rank = 0; rank < 8; rank++)
    {
        for (int file = 0; file < 8; file++)
        {
            // convertfile and ranke to sqare index
            int square = rank * 8 + file;
            if (file == 0)
            {
                std::cout << (8 - rank);
                std::cout << " ";
            }
            std::cout << (get_bit(bitboard, square) ? 1 : 0);
            std::cout << " ";
        }
        // Print new line every rank
        std::cout << "\n";
    }
    std::cout << "  a b c d e f g h";

    std::cout << "\nBitboard: ";
    std::cout << bitboard;
    std::cout << "\n\n";
}

int main()
{
        

    return 0;
}