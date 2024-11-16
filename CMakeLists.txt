cmake_minimum_required(VERSION 3.5)
project(grpc_sql_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Protobuf and gRPC packages
find_package(Protobuf REQUIRED CONFIG)
find_package(gRPC REQUIRED CONFIG)

# Workaround for missing Protobuf targets
if (NOT TARGET protobuf::libupb)
    add_library(protobuf::libupb INTERFACE IMPORTED)
endif()
if (NOT TARGET protobuf::protoc-gen-upb)
    add_library(protobuf::protoc-gen-upb INTERFACE IMPORTED)
endif()
if (NOT TARGET protobuf::protoc-gen-upbdefs)
    add_library(protobuf::protoc-gen-upbdefs INTERFACE IMPORTED)
endif()
if (NOT TARGET protobuf::protoc-gen-upb_minitable)
    add_library(protobuf::protoc-gen-upb_minitable INTERFACE IMPORTED)
endif()

set(PROTO_SRC proto/sql_service.pb.cc)
set(PROTO_HDR proto/sql_service.pb.h)
set(GRPC_SRC proto/sql_service.grpc.pb.cc)
set(GRPC_HDR proto/sql_service.grpc.pb.h)

include_directories(/Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/sql-parser/src)
link_directories(/Users/sharan/Desktop/workplace/IIT/SEM01/CS546/term-project/sql-parser)

include_directories(${CMAKE_SOURCE_DIR}/proto)
include_directories(${CMAKE_SOURCE_DIR}/query_router/include)
include_directories(${CMAKE_SOURCE_DIR}/common/include)
include_directories(${CMAKE_SOURCE_DIR}/exception/include)
include_directories(${CMAKE_SOURCE_DIR}/config/include)
include_directories(${CMAKE_SOURCE_DIR}/chronolog/include)
include_directories(${CMAKE_SOURCE_DIR}/event/include)
include_directories(${CMAKE_SOURCE_DIR}/event_writer/include)
include_directories(${CMAKE_SOURCE_DIR}/event_reader/include)
include_directories(${CMAKE_SOURCE_DIR}/event_generator/include)
include_directories(${CMAKE_SOURCE_DIR}/rapidjson/include)

add_executable(event_generator
            event_generator/event_generator_main.cpp
            event_generator/EventGenerator.cpp
            event_generator/EventGeneratorFactory.cpp
            event_generator/KeyValueEventGenerator.cpp
            event_generator/KeyValueEventGeneratorFactory.cpp  
            common/Constants.cpp
            common/typedefs.cpp
            common/MemoryIndex.cpp
            common/MemoryEventStorage.cpp
            exception/ChronicleNotFoundException.cpp
            exception/FieldNotFoundException.cpp
            exception/InvalidAggregationException.cpp
            exception/InvalidWindowArgumentException.cpp
            exception/UnrecognizedDayOfTheWeek.cpp
            config/ConfigConstants.cpp
            config/ConfigurationManager.cpp
            config/ConfigurationValues.cpp
            config/Enumerations.cpp
            chronolog/ChronoLog.cpp
            event/Event.cpp
            event/KeyValueEvent.cpp
            event_writer/EventWriter.cpp
            event_writer/EventWriterFactory.cpp
            event_writer/EventWriterUtils.cpp
            event_writer/FSKeyValueEventWriter.cpp
            event_writer/FSKeyValueEventWriterFactory.cpp
            event_writer/FSMemoryKeyValueEventWriter.cpp
            event_writer/FSMemoryKeyValueEventWriterFactory.cpp
            event_writer/IndexedKeyValueEventWriter.cpp
            event_writer/IndexedKeyValueEventWriterFactory.cpp
            event_reader/EventReader.cpp
            event_reader/DiskEventReader.cpp
            event_reader/EventReaderFactory.cpp
            event_reader/FSEventReader.cpp
            event_reader/FSEventReaderFactory.cpp
            event_reader/IndexedEventReader.cpp
            event_reader/IndexedEventReaderFactory.cpp
            event_reader/MemEventReader.cpp
            event_reader/MemEventReaderFactory.cpp
)

# Build the SQL client executable
add_executable(sql_client sql_client/sql_client.cpp ${PROTO_SRC} ${GRPC_SRC})
target_link_libraries(sql_client protobuf::libprotobuf gRPC::grpc++ protobuf::libprotoc)

# Build the SQL server executable
add_executable(query_router_server 
    query_router/query_router_server.cpp
    query_router/WorkerClient.cpp
    query_router/parser/ChronoSQLParser.cpp 
    query_router/parser/SelectExpression.cpp 
    query_router/parser/ConditionExpression.cpp
    query_router/parser/EventInterval.cpp
    query_router/parser/GroupByExpression.cpp
    common/Constants.cpp
    common/typedefs.cpp
    common/MemoryIndex.cpp
    common/MemoryEventStorage.cpp
    exception/ChronicleNotFoundException.cpp
    exception/FieldNotFoundException.cpp
    exception/InvalidAggregationException.cpp
    exception/InvalidWindowArgumentException.cpp
    exception/UnrecognizedDayOfTheWeek.cpp
    config/ConfigConstants.cpp
    config/ConfigurationManager.cpp
    config/ConfigurationValues.cpp
    config/Enumerations.cpp
    chronolog/ChronoLog.cpp
    event/Event.cpp
    event/KeyValueEvent.cpp
    event_writer/EventWriter.cpp
    event_writer/EventWriterFactory.cpp
    event_writer/EventWriterUtils.cpp
    event_writer/FSKeyValueEventWriter.cpp
    event_writer/FSKeyValueEventWriterFactory.cpp
    event_writer/FSMemoryKeyValueEventWriter.cpp
    event_writer/FSMemoryKeyValueEventWriterFactory.cpp
    event_writer/IndexedKeyValueEventWriter.cpp
    event_writer/IndexedKeyValueEventWriterFactory.cpp
    event_reader/EventReader.cpp
    event_reader/DiskEventReader.cpp
    event_reader/EventReaderFactory.cpp
    event_reader/FSEventReader.cpp
    event_reader/FSEventReaderFactory.cpp
    event_reader/IndexedEventReader.cpp
    event_reader/IndexedEventReaderFactory.cpp
    event_reader/MemEventReader.cpp
    event_reader/MemEventReaderFactory.cpp
    proto/worker_service.pb.cc 
    proto/worker_service.grpc.pb.cc
    ${PROTO_SRC} 
    ${GRPC_SRC})

target_link_libraries(query_router_server protobuf::libprotobuf gRPC::grpc++ protobuf::libprotoc sqlparser)

add_executable(worker_server 
    worker/worker_server.cpp 
    common/Constants.cpp
    common/typedefs.cpp
    common/MemoryIndex.cpp
    common/MemoryEventStorage.cpp
    config/ConfigConstants.cpp
    config/ConfigurationManager.cpp
    config/ConfigurationValues.cpp
    config/Enumerations.cpp
    chronolog/ChronoLog.cpp
    event/Event.cpp
    event/KeyValueEvent.cpp
    event_writer/EventWriter.cpp
    event_writer/EventWriterFactory.cpp
    event_writer/EventWriterUtils.cpp
    event_writer/FSKeyValueEventWriter.cpp
    event_writer/FSKeyValueEventWriterFactory.cpp
    event_writer/FSMemoryKeyValueEventWriter.cpp
    event_writer/FSMemoryKeyValueEventWriterFactory.cpp
    event_writer/IndexedKeyValueEventWriter.cpp
    event_writer/IndexedKeyValueEventWriterFactory.cpp
    event_reader/EventReader.cpp
    event_reader/DiskEventReader.cpp
    event_reader/EventReaderFactory.cpp
    event_reader/FSEventReader.cpp
    event_reader/FSEventReaderFactory.cpp
    event_reader/IndexedEventReader.cpp
    event_reader/IndexedEventReaderFactory.cpp
    event_reader/MemEventReader.cpp
    event_reader/MemEventReaderFactory.cpp
    exception/ChronicleNotFoundException.cpp
    exception/FieldNotFoundException.cpp
    exception/InvalidAggregationException.cpp
    exception/InvalidWindowArgumentException.cpp
    exception/UnrecognizedDayOfTheWeek.cpp
    proto/worker_service.pb.cc 
    proto/worker_service.grpc.pb.cc
)

target_link_libraries(worker_server 
    protobuf::libprotobuf 
    gRPC::grpc++ 
    protobuf::libprotoc 
)

# add_executable(worker_client 
#     test/worker_client/worker_client.cpp
#     common/Constants.cpp
#     common/typedefs.cpp
#     common/MemoryIndex.cpp
#     common/MemoryEventStorage.cpp
#     config/ConfigConstants.cpp
#     config/ConfigurationManager.cpp
#     config/ConfigurationValues.cpp
#     config/Enumerations.cpp
#     chronolog/ChronoLog.cpp
#     event/Event.cpp
#     event/KeyValueEvent.cpp
#     event_writer/EventWriter.cpp
#     event_writer/EventWriterFactory.cpp
#     event_writer/EventWriterUtils.cpp
#     event_writer/FSKeyValueEventWriter.cpp
#     event_writer/FSKeyValueEventWriterFactory.cpp
#     event_writer/FSMemoryKeyValueEventWriter.cpp
#     event_writer/FSMemoryKeyValueEventWriterFactory.cpp
#     event_writer/IndexedKeyValueEventWriter.cpp
#     event_writer/IndexedKeyValueEventWriterFactory.cpp
#     event_reader/EventReader.cpp
#     event_reader/DiskEventReader.cpp
#     event_reader/EventReaderFactory.cpp
#     event_reader/FSEventReader.cpp
#     event_reader/FSEventReaderFactory.cpp
#     event_reader/IndexedEventReader.cpp
#     event_reader/IndexedEventReaderFactory.cpp
#     event_reader/MemEventReader.cpp
#     event_reader/MemEventReaderFactory.cpp
#     exception/ChronicleNotFoundException.cpp
#     exception/FieldNotFoundException.cpp
#     exception/InvalidAggregationException.cpp
#     exception/InvalidWindowArgumentException.cpp
#     exception/UnrecognizedDayOfTheWeek.cpp
#     proto/worker_service.pb.cc 
#     proto/worker_service.grpc.pb.cc
# )

# target_link_libraries(worker_client 
#     protobuf::libprotobuf 
#     gRPC::grpc++ 
#     protobuf::libprotoc 
# )