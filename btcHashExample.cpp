// // #include "cryptlib.h"
// // #include "sha.h"
#include <iostream>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cstdlib>
#include <iomanip>

using namespace std;
using namespace CryptoPP;

int main (int argc, char* argv[])
{
    std::string msg = "01000000" 
        "81cd02ab7e569e8bcd9317e2fe99f2de44d49ab2b8851ba4a308000000000000" 
        "e320b6c2fffc8d750423db8b1eb942ae710e951ed797f7affc8892b0f1fc122b"
        "c7f5d74d" 
        "f2b9441a"
        "42a1469"
    ;
    
    cout << "Text Size: " << msg.size() << std::endl;
    
    byte decoded[80];
    
    HexDecoder decoder;

    decoder.Put((byte*)msg.data(), msg.size());
    decoder.MessageEnd();
    cout << "Binary Bytes: " << decoder.MaxRetrievable() << endl;
    decoder.Get(decoded, sizeof(decoded));

    for(int i = 0; i < 80; i++){
        cout << hex << " " << (unsigned int)decoded[i];
    };
    cout << std::endl;
    byte digest[32]; //bit = 32 * 8 = 256 bit

    SHA256 hash;
    hash.Update((const byte*)decoded, sizeof(decoded)); 
    hash.Final(digest);

    cout << "digest: ";
    for(int i = 0; i < sizeof(digest); i++){
        cout << hex << " " << (unsigned int)digest[i];
    };

    cout << endl;

    // Second SHA256

    cout << "_____Second Digest_______"<< endl;
    
    byte digest2[32]; //bit = 32 * 8 = 256 bit

    SHA256 hash2;
    hash2.Update((const byte*)digest, sizeof(digest)); 
    hash2.Final(digest2);

    cout << "digest2: ";
    for(int i = 0; i < sizeof(digest2); i++){
        cout << hex << setfill('0') << setw(2) << (unsigned int)digest2[i] << " ";
    };

    cout << endl;



    return 0; 
}


/*81 HexDecoder
128 64  32 16  8 4 2 1 
1   0   0  0   0 0 0 1  
128 + 1 = 129*/
