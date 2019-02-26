#include <stdio.h>
#include <curl/curl.h>
 #include <stdlib.h>
#include <string.h>


size_t callback_func(void *ptr, size_t size, size_t count, void *stream) {
  /* ptr - your string variable.
  stream - data chuck you received */
//prints chunck of data for each call.
printf("res %s \n \n", (char*)stream); 
}
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) { 
    return size;
}

int main(void)
{
    FILE* fichier = NULL;
    struct curl_slist *headerlist=NULL;
    fichier = fopen("/home/wafa/stt/0001.flac", "rb");

 

     CURL *curl;
     CURLcode res;



  /* get a curl handle */ 
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */ 
   
    curl_easy_setopt(curl, CURLOPT_URL, "https://gateway-lon.watsonplatform.net/speech-to-text/api/v1/recognize?key=Yqo-whkwaaeYCY5j8p_0M0ak-rCtBA0IDDwZQz2fflQT&objectMode=false&part_content_type='audio/flac'");
   
headerlist = curl_slist_append(headerlist,"Content-Type: audio/flac");
curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
  /* Now specify we want to POST data */ 
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    /* set where to read from (on Windows you need to use READFUNCTION too) */ 
    curl_easy_setopt(curl, CURLOPT_READDATA, fichier);
    /* we want to use our own read function */ 

  FILE *fp = fopen("resp.txt", "wb");

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
 
    /* Perform the request, res will get the return code */ 
  res = curl_easy_perform(curl);
  fclose(fp);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
}
