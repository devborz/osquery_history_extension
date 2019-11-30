// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>

#include <Json.h>
TEST(Parse, Text){
	std::string text = R"({ "lastname" : "Ivanov" , "firstname" : "Ivan" ,  "age" : 25 , "islegal" : false , "marks" : [ 4 , 5 , 5 , 5 , 2 , 3 ] , "address" : {  "city" : "Moscow" ,  "street" : "Vozdvijenka" } })";
	//text = Json::conv(text);
	Json object = Json::parse(text);
	EXPECT_EQ( "Ivanov", std::any_cast<std::string>(object["lastname"]));
	EXPECT_EQ(false, std::any_cast<bool>(object["islegal"]));
	EXPECT_EQ(25 ,std::any_cast<int>(object["age"]));

	auto marks = std::any_cast<std::vector<std::any>>(object["marks"]);
	EXPECT_EQ(4, std::any_cast<int>(marks[0]));
	EXPECT_EQ(5, std::any_cast<int>(marks[1]));

	auto address = std::any_cast<std::map<std::string, std::any>>(object["address"]);
	EXPECT_EQ("Moscow", std::any_cast<std::string>(address["city"]));
	EXPECT_EQ("Vozdvijenka", std::any_cast<std::string>(address["street"]));
}
int main(int argc, char **argv) {
	  ::testing::InitGoogleTest(&argc, argv);
	    return RUN_ALL_TESTS();
}
