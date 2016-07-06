// my first program in C++
#include <ctime>
#include <iostream>
#include <locale>
#include <vector>
//using namespace std;

std::string woot() {
  return {};
}

std::string weet() {
  return "";
}

int main()
{
    std::locale::global(std::locale("en_US.UTF-8"));
    std::time_t t = std::time(NULL);
    char mbstr[100];
    int doy;
    std::vector<std::string> scale_method {"two octave blind", "contrary motion", "Hanon"};
    std::vector<std::string> broken_chord_direction {"right", "left"};
    if (std::strftime(mbstr, sizeof(mbstr), "%j", std::localtime(&t))) {
        doy = std::stoi(mbstr);
        std::cout << "day of year = " << doy << '\n';
        std::cout << "You should practice scales with " << scale_method[doy % scale_method.size()] << ".\n";
        std::cout << "You should advance broken chords to the " << broken_chord_direction[doy % broken_chord_direction.size()] << ".\n";
    }
    std::cout << "woot" << woot() << "woot\n";
    std::cout << "weet" << weet() << "weet\n";

}
