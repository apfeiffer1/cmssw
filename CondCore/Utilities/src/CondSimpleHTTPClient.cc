
#include "CondSimpleHTTPClient.h"

namespace http = boost::network::http;
namespace uri = boost::network::uri;

namespace {
  std::string get_filename(const uri::uri &url) {
    std::string path = uri::path(url);
    std::size_t index = path.find_last_of('/');
    std::string filename = path.substr(index + 1);
    return filename.empty()? "index.html" : filename;
  }
} // namespace

namespace cond {
  int simpleHTTPClient( std::string url ) {

  try {
    http::client client;
    http::client::request request(url);
    http::client::response response = client.get(request);

    std::string filename = get_filename(request.uri());
    std::cout << "Saving to: " << filename << std::endl;
    std::ofstream ofs(filename.c_str());
    ofs << static_cast<std::string>(body(response)) << std::endl;
  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
  }
} // end namespace cond
