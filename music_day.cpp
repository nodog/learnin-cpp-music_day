#pragma once

#include "music_day.hpp"

#include <ctime>
#include <iostream>
#include <locale>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>

std::string MusicDay::day_practice(std::tm *ltm, int this_seed) {
    char mbstr[100];
    std::strftime(mbstr, sizeof(mbstr), "Today is %a, %F, day %j of %Y, so ", ltm);
    return mbstr + std::to_string(this_seed) + " is the random seed.\n";;
}

std::string MusicDay::choose_one_string(const std::string choices[], int array_size) {
    std::uniform_int_distribution<> dis(0, array_size - 1);
    int choice_index = dis(rand_generator);
    std::string choice = choices[choice_index];
    return choice;
}

std::string MusicDay::choose_one_string(std::vector<std::string> choices) {
    std::uniform_int_distribution<> dis(0, choices.size() - 1);
    int choice_index = dis(rand_generator);
    std::string choice = choices[choice_index];
    return choice;
}

std::string MusicDay::read_file_into_string(std::string filename) {
    std::string line;
    std::ifstream file_stream(filename);
    std::string string_of_file;
    if (file_stream.is_open()) {
        while (std::getline (file_stream, line)) {
            string_of_file += line + "\n";
        }
        file_stream.close();
    }
    else {
        std::cout << "Unable to open file";
    }
    file_stream.close();
    return string_of_file;
}

void MusicDay::read_file_into_vector(std::string filename, std::vector<std::string>* in_vector) {
    auto string_of_file = read_file_into_string(filename);
    std::istringstream stream_of_file(string_of_file);
    std::string line;
    while (std::getline(stream_of_file, line)) {
        in_vector->push_back(line);
    }
    return;
}

std::string MusicDay::schedule() {
    return read_file_into_string("music_day-schedule.txt");
}

std::string MusicDay::key_practice() {
    std::string describe_key_practice;

    read_file_into_vector("music_day-keys.txt", &keys);
    std::string day_key = choose_one_string(keys);
    describe_key_practice += day_key + "   is today's practice key.\n";

    read_file_into_vector("music_day-scale_methods.txt", &scale_methods);
    std::string scale_method = choose_one_string(scale_methods);
    describe_key_practice +=  scale_method;
    if (scale_method == scale_methods[0]) {
        std::uniform_int_distribution<> dis(1, 6);
        int hanon_index = dis(rand_generator);
        describe_key_practice += " " + std::to_string(hanon_index);
    }
    describe_key_practice += "   is today's scale method.\n";

    read_file_into_vector("music_day-scale_articulations.txt", &scale_articulations);
    std::string scale_articulation = choose_one_string(scale_articulations);
    describe_key_practice +=  scale_articulation + "   is today's scale articulation.\n";

    return describe_key_practice;
}

std::string MusicDay::chord_method_practice() {
    std::string describe_chord_method_practice;

    read_file_into_vector("music_day-chord_methods.txt", &chord_methods);
    std::string chord_method = choose_one_string(chord_methods);
    describe_chord_method_practice += chord_method + "   is today's chord method.\n";

    read_file_into_vector("music_day-directions.txt", &directions);
    std::string direction = choose_one_string(directions);
    describe_chord_method_practice += direction + "   is today's chord start direction.\n";

    read_file_into_vector("music_day-chord_types.txt", &chord_types);
    std::string chord_type = choose_one_string(chord_types);
    describe_chord_method_practice += chord_type + "  is today's chord type.\n";

    return describe_chord_method_practice;
}

std::string MusicDay::hand_independence_practice() {
    std::string describe_hand_independence_practice;

    read_file_into_vector("music_day-left_hand.txt", &left_hand_methods);
    std::string left_hand_method = choose_one_string(left_hand_methods);
    describe_hand_independence_practice += "LH method is   " + left_hand_method + ".\n";

    read_file_into_vector("music_day-right_hand.txt", &right_hand_methods);
    std::string right_hand_method = choose_one_string(right_hand_methods);
    describe_hand_independence_practice += "RH method is   " + right_hand_method + ".\n";

    return describe_hand_independence_practice;
}

MusicDay::MusicDay() {
}

std::string MusicDay::describe() {
    std::locale::global(std::locale("en_US.UTF-8"));
    std::time_t t = std::time(nullptr);
    std::tm *ltm = localtime(&t);
    auto year = 1900 + ltm->tm_year;
    auto yday = ltm->tm_yday;
    auto seed = year*1000 + yday + 1;
    std::mt19937 gen;
    gen.seed(seed);
    rand_generator = gen;

    std::string describe_practice;
    describe_practice += schedule();
    describe_practice += day_practice(ltm, seed);
    describe_practice += key_practice();
    describe_practice += chord_method_practice();
    describe_practice += hand_independence_practice();
    return describe_practice;
}
