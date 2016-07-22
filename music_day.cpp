// music_day
#include <ctime>
#include <iostream>
#include <locale>
#include <vector>
#include <random>
//using namespace std;

class MusicDay {
    //std::string key_initializer[];
    //std::vector<std::string> keys (key_initializer, key_initializer + sizeof(key_initializer) / sizeof(key_initializer[0]) );


    const static int KeySize = 24;
    const std::string keys[KeySize] =
    {"C","G","D","A","E","B","F#","C#","Ab","Eb","Bb","F",
        "Cm","Gm","Dm","Am","Em","Bm","F#m","C#m","Abm","Ebm","Bbm","Fm"};

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

    std::string key_practice() {
        std::uniform_int_distribution<> dis(0, KeySize - 1);
        int key_index = dis(rand_generator);
        std::string day_key = keys[key_index];
        return "Today's practice key is " + day_key;
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
