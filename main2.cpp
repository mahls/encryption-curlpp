// // #include "cryptlib.h"
// // #include "sha.h"
#include <iostream>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cstdlib>

int main (int argc, char* argv[])
{
// using namespace CryptoPP;
// SHA256 hash;	
// std::cout << "Name: " << hash.AlgorithmName() << std::endl;
// std::cout << "Digest size: " << hash.DigestSize() << std::endl;
// std::cout << "Block size: " << hash.BlockSize() << std::endl;

int nonce = 1000;

using namespace CryptoPP;

HexEncoder encoder(new FileSink(std::cout));

std::string digest;

while(true){

    std::string msg = "v411 5cf083427fde9444f853ca40694a2aa1037a1ece935d1804e4df23cc073ae4d1 5cf083427fde9444f853ca40694a2aa1037a1ece935d1804e4df23cc073ae4d1 1.jan 4555 " + std::to_string(nonce);
    nonce++;

    SHA256 hash;
    hash.Update((const byte*)msg.data(), msg.size());
    digest.resize(hash.DigestSize());
    hash.Final((byte*)&digest[0]);

    if(digest[0] == 0 && digest[1] == 0 && digest[2] == 0) {

        std::cout << "Message: " << msg << std::endl;

        std::cout << "Digest: ";
        StringSource(digest, true, new Redirector(encoder));
        std::cout << std::endl;

    };

};

return 0; 
}
