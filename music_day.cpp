// music_day
#include <ctime>
#include <iostream>
#include <locale>
#include <vector>
#include <random>
#include <fstream>
#include <vector>
//using namespace std;

class MusicDay {

    std::vector<std::string> keys;
    std::vector<std::string> key_methods;
    std::vector<std::string> chord_methods;
    std::vector<std::string> directions;
    std::vector<std::string> chord_types;

    int today;
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

    std::string day_practice() {
        return "Today is day " + std::to_string(today) + " of the year.\n";
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

    void read_file_into_vector(std::string filename, std::vector<std::string>* in_vector) {
        std::string line;
        std::ifstream file_stream(filename);
        if (file_stream.is_open())
		{
			while (std::getline (file_stream, line)) {
                in_vector->push_back(line);
			}
			file_stream.close();
            //std::cout << std::to_string(keys.size()) << " keys.\n";
		}

    else std::cout << "Unable to open file";
    file_stream.close();
    return;
}

    std::string key_practice() {
        std::string describe_key_practice;

        read_file_into_vector("music_day-keys.txt", &keys);
        std::string day_key = choose_one_string(keys);
        describe_key_practice += "Today's practice key is " + day_key + ".\n";

        read_file_into_vector("music_day-key_methods.txt", &key_methods);
        std::string key_method = choose_one_string(key_methods);
        describe_key_practice += "Today's key practice method is " + key_method;
        if (key_method == key_methods[0]) {
            std::uniform_int_distribution<> dis(1, 6);
            int hanon_index = dis(rand_generator);
            describe_key_practice += " " + std::to_string(hanon_index);
        }
        describe_key_practice += ".\n";

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

    public:
    MusicDay() {
        std::random_device rd;
        std::mt19937 gen(rd());
        rand_generator = gen;
        today = calc_day_of_year();
    }

    std::string describe() {
        std::string describe_practice;
        describe_practice += day_practice();
        describe_practice += key_practice();
        describe_practice += chord_method_practice();
        return describe_practice;
    }
};

int main()
{
    MusicDay md;
    std::cout << md.describe();
    int doy;
    std::vector<std::string> scale_method {"two octave blind", "contrary motion", "Hanon"};
    std::vector<std::string> broken_chord_direction {"right", "left"};
    //if ((doy = day_of_year()) > 0) {
    //    std::cout << "day of year = " << doy << '\n';
    //    std::cout << "You should practice scales with " << scale_method[doy % scale_method.size()] << ".\n";
    //    std::cout << "You should advance broken chords to the " << broken_chord_direction[doy % broken_chord_direction.size()] << ".\n";
}
