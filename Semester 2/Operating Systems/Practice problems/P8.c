#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
pthread_rwlock_t rwlock;

void * write_1(void *temp) {
        FILE *file1;
        char *str;
        pthread_rwlock_wrlock(&rwlock);
        printf("\nFile locked, please enter the message \n");
        str=(char *)malloc(10*sizeof(char));
        file1=fopen("temp","w");
        scanf("%s",str);
        fprintf(file1,"%s",str);
        fclose(file1);
        pthread_rwlock_unlock(&rwlock);
        printf("\nUnlocked the file you can read it now \n");
        free(str);
        return NULL;
}

void * write_2(void *temp) {
        FILE *file1;
        char *str;
        sleep(3);
        pthread_rwlock_wrlock(&rwlock);
        printf("\nFile locked, please enter the message \n");
        str=(char *)malloc(10*sizeof(char));
        file1=fopen("temp","a");
        scanf("%s",str);
        fprintf(file1,"%s",str);
        fclose(file1);
        pthread_rwlock_unlock(&rwlock);
        printf("\nUnlocked the file you can read it now \n");
        free(str);
        return NULL;
}

void * read_1(void *temp) {
        FILE *file1;
        char *str;
        sleep(5);
        pthread_rwlock_rdlock(&rwlock);
	printf("\n1 Opening file for reading\n");
        file1=fopen("temp","r");
        str=(char *)malloc(10*sizeof(char));
        fscanf(file1,"%s",str);
        printf("\nMessage from file is %s \n",str);
        sleep(3);

        fclose(file1);
        printf("\nUnlocking rwlock\n");
        pthread_rwlock_unlock(&rwlock);
        free(str);
        return NULL;
}

void * read_2(void *temp) {
        FILE *file1;
        char *str;
        sleep(6);
        pthread_rwlock_rdlock(&rwlock);
        printf("\n2 Opening file for reading\n");
        file1=fopen("temp","r");
        str=(char *)malloc(10*sizeof(char));
        fscanf(file1,"%s",str);
        printf("\nMessage from file is %s \n",str);

        fclose(file1);
        pthread_rwlock_unlock(&rwlock);
        free(str);
        return NULL;
}

int main(int argc, char** argv)
{
        pthread_t thread_id,thread_id1,thread_id3,thread_id4;
        void *res;
        pthread_rwlock_init(&rwlock,NULL);
        pthread_create(&thread_id,NULL,&write_1,NULL);
        pthread_create(&thread_id1,NULL,&read_1,NULL);

        pthread_create(&thread_id3,NULL,&read_2,NULL);

        pthread_create(&thread_id4,NULL,&write_2,NULL);
        printf("\n Created thread");
        pthread_join(thread_id,&res);
	pthread_join(thread_id1,&res);
        pthread_join(thread_id3,&res);

        pthread_join(thread_id4,&res);
        pthread_rwlock_destroy(&rwlock);

        return 0;
}