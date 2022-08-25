#include "ex01.h"

int main()
{
    t_art dog;
    t_art cat;

    dog.art = get_dog_art();
    cat.art = get_cat_art();

    dog.fd = open("master", O_WRONLY | O_CREAT | O_APPEND, 0644);
    cat.fd = open("master", O_WRONLY | O_CREAT | O_APPEND, 0644);

    pthread_create(&dog.pid, NULL, commit, (void*)&dog);
    pthread_create(&cat.pid, NULL, commit, (void*)&cat);

    pthread_join(dog.pid, NULL);
    pthread_join(cat.pid, NULL);
}