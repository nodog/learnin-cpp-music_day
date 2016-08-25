// music_day
#include <ctime>
#include <iostream>
#include <locale>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>

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

    int calc_day_of_year() {
        std::locale::global(std::locale("en_US.UTF-8"));
        std::time_t t = std::time(NULL);
        char mbstr[100];
        if (std::strftime(mbstr, sizeof(mbstr), "%j", std::localtime(&t))) {
            return std::stoi(mbstr);
        } else {
            return 0;
        }
    }

    int calc_year() {
        std::locale::global(std::locale("en_US.UTF-8"));
        std::time_t t = std::time(NULL);
        char mbstr[100];
        if (std::strftime(mbstr, sizeof(mbstr), "%Y", std::localtime(&t))) {
            return std::stoi(mbstr);
        } else {
            return 0;
        }
    }

    std::string day_practice(int today, int this_year, int this_seed) {
        return "Today is day " + std::to_string(today) + " of the year " + std::to_string(this_year)
            + ", so the rand seed is " + std::to_string(this_seed) + ".\n";
    }

    std::string choose_one_string(const std::string choices[], int array_size) {
        std::uniform_int_distribution<> dis(0, array_size - 1);
        int choice_index = dis(rand_generator);
        std::string choice = choices[choice_index];
        return choice;
    }

    std::string choose_one_string(std::vector<std::string> choices) {
        std::uniform_int_distribution<> dis(0, choices.size() - 1);
        int choice_index = dis(rand_generator);
        std::string choice = choices[choice_index];
        return choice;
    }

    std::string read_file_into_string(std::string filename) {
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

    void read_file_into_vector(std::string filename, std::vector<std::string>* in_vector) {
        auto string_of_file = read_file_into_string(filename);
        std::istringstream stream_of_file(string_of_file);
        std::string line;
        while (std::getline(stream_of_file, line)) {
            in_vector->push_back(line);
        }
        return;
    }

    std::string schedule() {
      return read_file_into_string("music_day-schedule.txt");
    }

    std::string key_practice() {
        std::string describe_key_practice;

        read_file_into_vector("music_day-keys.txt", &keys);
        std::string day_key = choose_one_string(keys);
        describe_key_practice += day_key + "   is today's practice key.\n";

        read_file_into_vector("music_day-scale_methods.txt", &scale_methods);
        std::string scale_method = choose_one_string(scale_methods);
        describe_key_practice +=  scale_method + "   is today's scale method";
        if (scale_method == scale_methods[0]) {
            std::uniform_int_distribution<> dis(1, 6);
            int hanon_index = dis(rand_generator);
            describe_key_practice += " " + std::to_string(hanon_index);
        }
        describe_key_practice += ".\n";

        std::cout << "happiness\n";

        read_file_into_vector("music_day-scale_articulations.txt", &scale_articulations);
        std::string scale_articulation = choose_one_string(scale_articulations);
        describe_key_practice +=  scale_articulation + "   is today's scale articulation.\n";
        
        std::cout << "sadness\n";

        return describe_key_practice;
    }

	std::string chord_method_practice() {
        std::string describe_chord_method_practice;

        read_file_into_vector("music_day-chord_methods.txt", &chord_methods);
        std::string chord_method = choose_one_string(chord_methods);
        describe_chord_method_practice += "Today's chord method is " + chord_method + ".\n";

        read_file_into_vector("music_day-directions.txt", &directions);
        std::string direction = choose_one_string(directions);
        describe_chord_method_practice += "Today's chord start direction is " + direction + ".\n";

        read_file_into_vector("music_day-chord_types.txt", &chord_types);
        std::string chord_type = choose_one_string(chord_types);
        describe_chord_method_practice += "Today's chord type is " + chord_type + ".\n";

		return describe_chord_method_practice;
 	}

	std::string hand_independence_practice() {
        std::string describe_hand_independence_practice;

        read_file_into_vector("music_day-left_hand.txt", &left_hand_methods);
        std::string left_hand_method = choose_one_string(left_hand_methods);
        describe_hand_independence_practice += "Play chords for the day (song or blues) or the circle of fifths these ways.\n";
        describe_hand_independence_practice += "Today's left hand method is " + left_hand_method + ".\n";

        read_file_into_vector("music_day-right_hand.txt", &right_hand_methods);
        std::string right_hand_method = choose_one_string(right_hand_methods);
        describe_hand_independence_practice += "Today's right hand method is " + right_hand_method + ".\n";

		return describe_hand_independence_practice;
 	}

    public:
    MusicDay() {
    }

    std::string describe() {
        auto today = calc_day_of_year();
        auto this_year = calc_year();
        auto this_seed = this_year*1000 + today;
        std::mt19937 gen;
        gen.seed(this_seed);
        rand_generator = gen;

        std::string describe_practice;
        describe_practice += schedule();
        describe_practice += day_practice(today, this_year, this_seed);
        describe_practice += key_practice();
        describe_practice += chord_method_practice();
        describe_practice += hand_independence_practice();
        return describe_practice;
    }
};

int main() {
    MusicDay md;
    std::cout << md.describe();
}
