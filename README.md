# Operating_Systems
# Coding projects for CS33211 at Kent State University

To compile and run the code, run the 3 commands listed below.
$ g++ producer.cpp -o producer -lrt -lpthread
$ g++ consumer.cpp -o consumer -lrt -lpthread
$ ./producer && ./consumer 

For this assignment, the producer can produce up to 2 items and store them in the shared table. The consumer can access this shared table and print the items in the table.
