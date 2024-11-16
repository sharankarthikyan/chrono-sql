#include <iostream>
#include "ConfigurationManager.h"
#include "KeyValueEventGenerator.h"
#include "EventWriterFactory.h"

int generateEvents(ConfigurationValues *config, int argc, char **argv) {
    // Event generation
    auto *generator = new KeyValueEventGenerator(config->payloadSize, config->payloadVariation,
                                                 config->lowerTimestamp, config->higherTimestamp);
    auto *writerFactory = new EventWriterFactory();
    EventWriter *eventWriter = writerFactory->getWriter(config);

    for (int i = 3; i < (argc - 1); i += 2) {
        std::list<Event *> events = generator->generateEvents(strtol(argv[i + 1], nullptr, 10));

        events.sort([](const Event *event1, const Event *event2) {
            return event1->getTimestamp() < event2->getTimestamp();
        });

        eventWriter->write(argv[i], events);
    }

    std::cout << "Generation of events finished" << std::endl;

    if (!strcmp(argv[argc - 1], "-t")) {
        return 1;
    }

    return 0;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Usage: ./event_generator <path_to_config_file> -g <log_name> <log_size>" << std::endl;
        return -1;
    }

    auto *config = (new ConfigurationManager(argv[1]))->getConfiguration();
    int testing = 0;

    if (argc > 2) {
        if (!strcmp(argv[2], "-g")) {
            // Generate events
            testing = generateEvents(config, argc, argv);
        } else if (!strcmp(argv[2], "-i")) {
            // Bring indexes to memory
            for (int i = 3; i < argc; i++) {
                if (!strcmp(argv[i], "-t")) {
                    testing = 1;
                    break;
                }
                std::string buf(argv[i]);
                MemoryIndex::generate(buf);
            }
        } else if (!strcmp(argv[2], "-t")) {
            // return executeTests(config);
        } else {
            std::cout << "Invalid arguments" << std::endl;
            return -1;
        }
        // return testing ? executeTests(config) : mainLoop(config);
    }
    return 1;
}