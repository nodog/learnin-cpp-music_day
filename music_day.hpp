#pragma once

#include <vector>
#include <random>

class MusicDay {

    std::vector<std::string> keys;
    std::vector<std::string> scale_methods;
    std::vector<std::string> scale_articulations;
    std::vector<std::string> chord_methods;
    std::vector<std::string> directions;
    std::vector<std::string> chord_types;
    std::vector<std::string> left_hand_methods;
    std::vector<std::string> right_hand_methods;

    std::mt19937 rand_generator;

    std::string choose_one_string(const std::string choices[], int array_size);
    std::string choose_one_string(std::vector<std::string> choices);
    std::string read_file_into_string(std::string filename);
    void read_file_into_vector(std::string filename, std::vector<std::string>* in_vector);

    std::string day_practice(std::tm *ltm, int this_seed);
    std::string schedule();
    std::string key_practice();
	std::string chord_method_practice();
	std::string hand_independence_practice();

    public:
    MusicDay();

    std::string describe();
};
