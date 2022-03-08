#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include<catch.hpp>

#include <../src/intentRecognition.h>

intentRecognition intent;


TEST_CASE("******* TEST WITH PROVIDED INPUTS ******** ", "[classic]")
{
	REQUIRE(intent.getIntent("What is the weather like today?") == " Intent : Get Weather");
	REQUIRE(intent.getIntent("What is the weather like in Paris today?") == " Intent : Get Weather City");
	REQUIRE(intent.getIntent("Tell me an interesting fact.") == " Intent : Get Fact");
};

TEST_CASE("******* TEST DIFFERENT USES CASES ********", "[classic]")
{
	
		REQUIRE(intent.getIntent("How is the weather today?") == " Intent : Get Weather");
		REQUIRE(intent.getIntent("How is the weather in Paris today?") == " Intent : Get Weather City");
		REQUIRE(intent.getIntent("Tell me something interesting.") == " Intent : Get Fact");
		REQUIRE(intent.getIntent("How is the weather in Paris today?") == " Intent : Get Weather City");
		REQUIRE(intent.getIntent("I want to know an interesting fact.") == " Intent : Get Fact");
		REQUIRE(intent.getIntent("Let's talk about an interesting fact.") == " Intent : Get Fact");
	
}
