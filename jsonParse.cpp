
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <string>

using json = nlohmann::json
using namespace curlpp::options;


int main(int, char **)
{

   using json = nlohmann::json;

   namespace ns {

        void to_json(json& j, const person& p) {
             j = json{ {"name", p.name}, {"address", p.address}, {"age", p.age} };
         }

        void from_json(const json& j, person& p) {
             j.at("name").get_to(p.name);
             j.at("address").get_to(p.address);
             j.at("age").get_to(p.age);
         }
    }

	try
	{
		curlpp::Cleanup myCleanup;
		curlpp::Easy myRequest;

		myRequest.setOpt<Url>("https://blockchain.info/rawblock/125552");
		myRequest.perform();

        //  std::ostringstream os;
        // string jsonBlockChain;
        // os << curlpp::options::Url("https://blockchain.info/rawblock/125552");
        // jsonBlockChain = os;
        // std::cout << jsonBlockChain << std::endl; 

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
