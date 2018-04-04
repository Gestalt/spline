#include "Application.h"
#include "Parameters.h"
#include "InterpolationException.h"
#include "Log.h"

static void help(const std::string& error) {
    log() << error;
    log() <<
        "      \n" <<
        "Usage:\n" <<
        "      [--source|-s]        file source with function points\n" <<
        "      [--destination|-d]   file source with arguments to be interpolated\n" <<
        "      [--output|-o]        output file. Default is <output.txt>\n" <<
        "      [--spline]           interpolation algorithm: [Neighbor|Linear|Quadric]\n" <<
        "      [--verbose|-v]       be verbose\n" <<
        "      [--help|-h]          print this message\n";
}

int main(int argc, char** argv) {
    Parameters params;

    try {
        const std::string error = params.parse(argc, argv);
        if (!error.empty()) {
            help(error);
            return 0;
        }
        Application::process(params);
    } catch (const InterpolationException& ex) {
        log() << "An interpolation exception occured. " << ex.what();
    } catch (const std::exception& ex) {
        log() << "An exception occured. " << ex.what();
    } catch (...) {
        log() << "An unknown  exception occured";
    }
    log() << "Success!";
	return 0;
}