#include <iostream>

// Define
// Primary variable for the bit borade 64 bits for 8 by 8 sqaure
#define U64 unsigned long long


// Enum board squares
enum
{
a8, b8, c8, d8, e8, f8, g8, h8,
a7, b7, c7, d7, e7, f7, g7, h7,
a6, b6, c6, d6, e6, f6, g6, h6,
a5, b5, c5, d5, e5, f5, g5, h5,
a4, b4, c4, d4, e4, f4, g4, h4,
a3, b3, c3, d3, e3, f3, g3, h3,
a2, b2, c2, d2, e2, f2, g2, h2,
a1, b1, c1, d1, e1, f1, g1, h1,

};

const char *square_to_cordinates[]{
"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",


};



enum
{
    white,
    black
};


/*Not a file

8 0 1 1 1 1 1 1 1
7 0 1 1 1 1 1 1 1
6 0 1 1 1 1 1 1 1
5 0 1 1 1 1 1 1 1
4 0 1 1 1 1 1 1 1
3 0 1 1 1 1 1 1 1
2 0 1 1 1 1 1 1 1
1 0 1 1 1 1 1 1 1
  a b c d e f g h

Bitboard: 18374403900871474942
Not h file
8 1 1 1 1 1 1 1 0
7 1 1 1 1 1 1 1 0
6 1 1 1 1 1 1 1 0
5 1 1 1 1 1 1 1 0
4 1 1 1 1 1 1 1 0
3 1 1 1 1 1 1 1 0
2 1 1 1 1 1 1 1 0
1 1 1 1 1 1 1 1 0
  a b c d e f g h
Bitboard: 9187201950435737471

not hg

8 1 1 1 1 1 1 0 0
7 1 1 1 1 1 1 0 0
6 1 1 1 1 1 1 0 0
5 1 1 1 1 1 1 0 0
4 1 1 1 1 1 1 0 0
3 1 1 1 1 1 1 0 0
2 1 1 1 1 1 1 0 0
1 1 1 1 1 1 1 0 0
  a b c d e f g h
Bitboard: 4557430888798830399

8 0 0 1 1 1 1 1 1
7 0 0 1 1 1 1 1 1
6 0 0 1 1 1 1 1 1
5 0 0 1 1 1 1 1 1
4 0 0 1 1 1 1 1 1
3 0 0 1 1 1 1 1 1
2 0 0 1 1 1 1 1 1
1 0 0 1 1 1 1 1 1
  a b c d e f g h
Bitboard: 18229723555195321596


*/
const U64 not_a_file = 18374403900871474942ULL;

const U64 not_h_file = 9187201950435737471ULL;

const U64 not_hg_file = 4557430888798830399ULL;

const U64 not_ab_file = 18229723555195321596ULL;


// Relevant occupancy bit count for every square on board for bishop
const int bishop_relevant_bits[64] {
    6, 5, 5, 5, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 9, 9, 7, 5, 5,
    5, 5, 7, 7, 7, 7, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5,
    6, 5, 5, 5, 5, 5, 5, 6
};

// Relevant occupancy bit count for every square on board for rook
const int rook_relevant_bits[64] {
    12, 11, 11, 11, 11, 11, 11, 12,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11,
    12, 11, 11, 11, 11, 11, 11, 12
};




void print_bitboard(U64 bitboard);



// Bit Macros //
// Get bit
#define get_bit(bitboard, square) (bitboard & (1ULL << square))
// Set bit
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
// Pop bit
#define pop_bit(bitboard, square) (get_bit(bitboard, square) ? bitboard ^= (1ULL << square) : 0)

// pawn attacks table
U64 pawn_attacks[2][64];

// knight attacks table
U64 knight_attacks[64];

// king attacks table
U64 king_attacks[64];



void getChessSquares()
{
    for (int rank = 8; rank >= 1; rank--)
    {
        std::cout << "\"" << "a" << rank << "\", ";
        std::cout << "\"" << "b" << rank << "\", ";
        std::cout << "\"" << "c" << rank << "\", ";
        std::cout << "\"" << "d" << rank << "\", ";
        std::cout << "\"" << "e" << rank << "\", ";
        std::cout << "\"" << "f" << rank << "\", ";
        std::cout << "\"" << "g" << rank << "\", ";
        std::cout << "\"" << "h" << rank << "\",\n";
        
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
// count bits within bitboard slow? O(1) but make 64 iterations ig
int count_bits (U64 bitboard){
    int bits = 0;

    while (bitboard){
        bitboard &= bitboard -1;
        bits++;
    }

    return bits;
}

// Get least signiifcant 1st bit index
int get_ls1b_index(U64 bitboard){
    if(bitboard){
        // Get trailing bits before 
        return count_bits((bitboard &= (-bitboard)) -1 );
    }else {
        return -1;
    }
}

// generate pawn attacks
U64 mask_pawn_attacks(int side,int square)
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
        if((bitboard >> 7 ) & not_a_file){attacks |= (bitboard >> 7 );}
        
        if((bitboard >> 9 ) & not_h_file){attacks |= (bitboard >> 9 );}
        

    } else {
    // black
        if((bitboard << 7 ) & not_h_file){attacks |= (bitboard << 7 );}
        if((bitboard << 9 ) & not_a_file){attacks |= (bitboard << 9 );}

        
    }

    // return attack map
    //print_bitboard(attacks);
    return attacks;
}
U64 mask_knight_attacks(int square){
    // 17 15,10,6
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    set_bit(bitboard, square);
    if((bitboard << 17 ) & not_a_file){attacks |= (bitboard << 17);}
    if((bitboard << 15 ) & not_h_file){attacks |= (bitboard << 15);}
    if((bitboard << 10 ) & not_ab_file){attacks |= (bitboard << 10);}
    if((bitboard << 6 ) & not_hg_file){attacks |= (bitboard << 6);}

    if((bitboard >> 17 ) & not_h_file){attacks |= (bitboard >> 17);}
    if((bitboard >> 15 ) & not_a_file){attacks |= (bitboard >> 15);}
    if((bitboard >> 10 ) & not_hg_file){attacks |= (bitboard >> 10);}
    if((bitboard >> 6 ) & not_ab_file){attacks |= (bitboard >> 6);}



    return attacks;
}

// masj king attack

U64 mask_king_attacks(int square){
    // 1 , 8, 7,9
    U64 attacks = 0ULL;
    U64 bitboard = 0ULL;
    set_bit(bitboard, square);

    attacks |= (bitboard << 8);
    attacks |= (bitboard >> 8);

    if((bitboard >> 9) & not_h_file){attacks |= (bitboard >> 9);}
    if((bitboard << 9) & not_a_file){attacks |= (bitboard << 9);}

    if((bitboard >> 7) & not_a_file){attacks |= (bitboard >> 7);}
    if((bitboard << 7) & not_h_file){attacks |= (bitboard << 7);}

    if((bitboard >> 1) & not_h_file){attacks |= (bitboard >> 1);}
    if((bitboard << 1) & not_a_file){attacks |= (bitboard << 1);}
 
    return attacks;    


}

// mask bishop attacks
U64 mask_bishop_attacks(int square){
    U64 attacks = 0ULL;
    // init ranks and files
    int r,f;
    //init target ranke and files
    int tr = square /8;
    int tf = square % 8;

    for (r = tr +1,f = tf +1; r <= 6 && f <=6; r++,f++){
        attacks |= (1ULL << ( r* 8 + f));
    }
    for (r = tr -1 ,f = tf +1; r >= 1 && f <=6; r--,f++){
        attacks |= (1ULL << ( r* 8 + f));
    }
    for (r = tr + 1 ,f = tf  - 1; r <= 6 && f >= 1; r++,f--){
        attacks |= (1ULL << ( r* 8 + f));
    }
    for (r = tr - 1 ,f = tf  - 1; r >= 1 && f >= 1; r--,f--){
        attacks |= (1ULL << ( r* 8 + f));
    }
    return attacks;
}

// mask rook attacks
U64 mask_rook_attacks(int square){
    U64 attacks = 0ULL;
    // init ranks and files
    int r,f;
    //init target ranke and files
    int tr = square /8;
    int tf = square % 8;

    for (r = tr +1; r <= 6 ; r++){
        attacks |= (1ULL << ( r* 8  +tf));
    }
    for (r = tr - 1; r >= 1 ; r--){
        attacks |= (1ULL << ( r* 8  +tf));
    }
    //tr = square /8;
    for (f = tf +1; f <= 6 ; f++){
        attacks |= (1ULL << ( tr* 8  +f));
    }
    for (f = tf - 1; f >= 1 ; f--){
        attacks |= (1ULL << ( tr* 8  +f));
    }
    
    return attacks;
}



// generate pishop attakcs on the fly
U64 generate_bishop_attacks(int square,U64 block){
    U64 attacks = 0ULL;
    // init ranks and files
    int r,f;
    int tr = square /8;
    int tf = square % 8;



    //generate bishop attacks
    for (r = tr +1,f = tf +1; r <= 7 && f <=7; r++,f++){
        
        attacks |= (1ULL << ( r* 8 + f));
        if (((1ULL) << (r * 8 + f)) & block ){
            break;
        }
    }
    for (r = tr -1 ,f = tf +1; r >= 0 && f <=7; r--,f++){
        attacks |= (1ULL << ( r* 8 + f));
        if (((1ULL) << (r * 8 + f)) & block ){
            break;
        }
    }
    for (r = tr + 1 ,f = tf  - 1; r <= 7 && f >= 0; r++,f--){
        attacks |= (1ULL << ( r* 8 + f));
        if (((1ULL) << (r * 8 + f)) & block ){
            break;
        }
    }
    for (r = tr - 1 ,f = tf  - 1; r >= 0 && f >= 0; r--,f--){
        attacks |= (1ULL << ( r* 8 + f));
        if (((1ULL) << (r * 8 + f)) & block ){
            break;
        }
    }
    return attacks;
}


U64 generate_rook_attacks(int square, U64 block){
    U64 attacks = 0ULL;
    // init ranks and files
    int r,f;
    //init target ranke and files
    int tr = square /8;
    int tf = square % 8;

    for (r = tr +1; r <= 7 ; r++){
        attacks |= (1ULL << ( r* 8  +tf));
        if (((1ULL) << ( r* 8  +tf)) & block ){
            break;
        }
    }
    for (r = tr - 1; r >= 0 ; r--){
        attacks |= (1ULL << ( r* 8  +tf));
        if (((1ULL) << ( r* 8  +tf)) & block ){
            break;
        }
    }
    //tr = square /8;
    for (f = tf +1; f <= 7 ; f++){
        attacks |= (1ULL << ( tr* 8  +f));
         if (((1ULL) << ( tr* 8  +f)) & block ){
            break;
        }
    }
    for (f = tf - 1; f >= 0 ; f--){
        attacks |= (1ULL << ( tr* 8  +f));
         if (((1ULL) << ( tr* 8  +f)) & block ){
            break;
        }
    }
    
    return attacks;
}


//Generate Pawn Attacks
void init_pawn_attacks(){
    for (int square = 0; square < 64; square++){
        pawn_attacks[white][square] = mask_pawn_attacks(white,square);
        pawn_attacks[black][square] = mask_pawn_attacks(black,square);


    }
}

void init_knight_attacks(){
    for (int square = 0; square <64; square++){
        knight_attacks[square]= mask_knight_attacks(square);
    }
}

void init_king_attacks(){
    for(int square = 0; square < 64; square++){
        knight_attacks[square] = mask_king_attacks(square);
        //print_bitboard(knight_attacks[square]);
    }   
}


void init_leaper_attacks(){
    init_king_attacks();
    init_knight_attacks();
    init_pawn_attacks();
}


//Set occupancies
U64 set_occupancy(int index, int bits_in_mask, U64 attack_mask){
    // Occupancy map
    U64 occupancy = 0ULL;

    for (int count = 0; count < bits_in_mask; count++){
        int square = get_ls1b_index(attack_mask);

        pop_bit(attack_mask,square);
        if(index & (1 << count)){
            //populate occuancy map
            set_bit(occupancy,square);

        }
    }

    return occupancy;
}


int main()
{
    init_leaper_attacks();

    for (int rank = 0; rank < 8; rank++){
        for (int file = 0; file < 8; file++){
            int square = rank * 8 + file;
            std::cout<< count_bits(mask_rook_attacks(square)) << ", ";
        }
        std::cout<< "\n";
    }

    return 0;
}