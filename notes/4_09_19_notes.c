
void * doSomeThing (void * arg) {
	
	pthread_mutex_lock(&lock);

	unsigned long i = 0;
	counter += 1;
	printf("\n Job &d started\n", counter);

	for (i = 0; i < (0xFFFFFFFF); i++);

	printf("\n Job %d finished\n", counter);

	pthread_mutex_unlock(&lock);

	return NULL;
}