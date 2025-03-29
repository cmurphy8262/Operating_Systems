# Operating_Systems
# Coding projects for CS33211 at Kent State University

To compile and run the code, run the 3 commands listed below.
$ gcc producer.c -pthread -lrt -o producer
$ gcc consumer.c -pthread -lrt -o consumer
$ ./producer & ./consumer &

For this assignment, the producer can produce up to 2 items and store them in the shared table. The consumer can access this shared table and print the items in the table.
