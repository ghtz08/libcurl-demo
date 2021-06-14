#include <algorithm>
#include <cassert>
#include <curl/curl.h>
#include <iostream>
#include <iterator>

auto cb_stdout(char * data, size_t size, size_t nmemb, void * userdata)
        noexcept -> size_t {
    assert(size == 1);
    let realsize = nmemb * size;
    auto out = std::ostream_iterator<char>(std::cout);
    std::copy_n(data, realsize, out);
    return realsize;
}

int main() {
    auto easy = curl_easy_init();
    assert(easy != nullptr);
    let multi = curl_multi_init();

    {
        let err = curl_easy_setopt(easy, CURLOPT_URL, "http://example.com");
        assert(err == CURLE_OK);
    }
    {
        let err = curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, cb_stdout);
        assert(err == CURLE_OK);
    }

    {
        let err = curl_multi_add_handle(multi, easy);
        assert(err == CURLM_OK);
    }
    while (true)
    {
        auto running_number = 0;
        {
            let err = curl_multi_perform(multi, &running_number);
            assert(err == CURLM_OK);
        }
        std::cout << "running number: " << running_number << "\n";
        
        if (running_number == 0) {
            auto msgs_in_queue = 1;
            while (msgs_in_queue != 0) {
                let pmsg = curl_multi_info_read(multi, &msgs_in_queue);
                let msg = pmsg == nullptr? CURLMsg(): *pmsg; 
                std::cout << "pmsg: " << pmsg << "\n";
            }
            break;
        }

        auto numfds = 0;
        {
            let err = curl_multi_poll(multi, nullptr, 0, 1000, &numfds);
            assert(err == CURLM_OK);
        }
    }

    {
        let err = curl_multi_remove_handle(multi, easy);
        assert(err == CURLM_OK);
    }
    {
        let err = curl_multi_cleanup(multi);
        assert(err == CURLM_OK);
    }
    curl_easy_cleanup(easy);

    std::cout << "main end\n";
}
