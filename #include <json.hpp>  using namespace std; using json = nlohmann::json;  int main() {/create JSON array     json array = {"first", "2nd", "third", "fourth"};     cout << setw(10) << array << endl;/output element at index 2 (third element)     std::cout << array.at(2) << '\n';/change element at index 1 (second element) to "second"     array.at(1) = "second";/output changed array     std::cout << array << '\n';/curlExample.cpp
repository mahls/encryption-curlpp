#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <sstream>
#include <json.hpp>

using json = nlohmann::json;
using namespace curlpp::options;
using namespace std;

int main(int, char **)
{
    stringstream response;
    string responseString;

	try
	{
		curlpp::Cleanup myCleanup;
		curlpp::Easy myRequest;
		
        myRequest.setOpt<Url>("https://blockchain.info/rawblock/125552");
		myRequest.setOpt(new curlpp::Options::WriteStream(&response)); // Using namespace, setting string stream for reuqest, response
        myRequest.perform();
       
        responseString = response.str();
        // cout << responseString << endl;

        json jsonBlock = json::parse(responseString); // Parsing
        // cout << setw(4) << jsonBlock << endl; // Operating Overloading on "<<"
       
        string strHash = jsonBlock["hash"];
        string strPrevBlockHash = jsonBlock["prev_block"];
        string strMerklRoot = jsonBlock["mrkl_root"];
        int intTime = jsonBlock["time"];
        unsigned int intBits = jsonBlock["bits"];
        unsigned int intNonce = jsonBlock["nonce"];
       
        cout << strHash << endl;
        cout << strPrevBlockHash << endl;
        cout << strMerklRoot << endl;
        cout << intTime << endl;
        cout << intBits << endl;
        cout << intNonce << endl;


        cout << endl << "_________________________<TRANSACTIONS>_________________________" << endl;
        int noTransaction = jsonBlock["n_tx"];
        for(int i = 0; i < noTransaction; i++){
            cout << "Transaction Number " << i <<": ";
            string txHash = jsonBlock["tx"][i]["hash"];
            cout << txHash << endl;
        };

	}

	catch(curlpp::RuntimeError & e)
	{
		std::cout << e.what() << std::endl;
	}

	catch(curlpp::LogicError & e)
	{
		std::cout << e.what() << std::endl;
	}
    
  return 0;
}
