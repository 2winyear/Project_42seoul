#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CNT_TEST 10

char* ft_get_filename(const char* path);

int         main() {
#if defined _WIN32
  const char* output[CNT_TEST] = {"article.pdf", "bar.exe", "index.html", NULL,
                                  NULL,          NULL,      NULL,         NULL,
                                  NULL,          NULL};
#elif defined __APPLE__
  const char* output[CNT_TEST] = {
      NULL,       NULL,         NULL,          NULL,
      "for_test", "index.html", "article.pdf", "article list.pdf",
      NULL,       NULL};
#endif

  const char* testcase[CNT_TEST] = {"C:\\Documents\\Newsletters\\article.pdf",
                                    "C:\\Program files\\foo\\bar.exe",
                                    "C:\\Program files\\Downloads\\index.html",
                                    "C:\\Program files\\Downloads\\",
                                    "/Users/Me/for_test",
                                    "/Users/Me/Downloads/index.html",
                                    "/usr/share/doc/bash/article.pdf",
                                    "/usr/share/doc/bash/article list.pdf",
                                    "/usr/share/",
                                    ""};

  for (int i = 0; i < CNT_TEST; i++) {
    char* filename = ft_get_filename(testcase[i]);
    printf("[Test case %d]\n\t%s", i, filename);
    if (filename == NULL && output[i] == NULL) {
      printf("\tOK\n");
    } else if (filename != NULL && output[i] != NULL) {
      if (strcmp(filename, output[i]) == 0) {
        printf("\tOK\n");
      } else {
        printf("\tFAIL\n");
        exit(1);
      }
    } else {
      printf("\tFAIL\n");
      exit(1);
    }
    free(filename);
    filename = NULL;
  }
}
