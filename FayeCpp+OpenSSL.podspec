Pod::Spec.new do |s|

# Common settings
  s.name         = "FayeCpp+OpenSSL"
  s.version      = "0.1.17"
  s.summary      = "Faye C++ lightweight, cross-platform client with Objective-C client wrapper."
  s.description  = <<-DESC
Faye C++ lightweight, cross-platform client with Objective-C client wrapper. 
Library created with Pure C++ (features provided by Standard C++), without heavy STL and C++11 features.
You can use Objective-C wrapper or C++ client directly.
                      DESC
  s.homepage     = "https://github.com/OlehKulykov/FayeCpp"
  s.license      = { :type => 'MIT', :file => 'LICENSE' }
  s.author       = { "Oleh Kulykov" => "info@resident.name" }
  s.source       = { :git => 'https://github.com/OlehKulykov/FayeCpp.git', :tag => s.version.to_s, :submodules => "true" }

# Platforms
  s.ios.deployment_target = "5.0"
  s.osx.deployment_target = "10.7"

# Build  
  s.public_header_files = 'fayecpp.h', 'contrib/objc/FayeCppClient.h'
  s.source_files = 'contrib/objc/*.{h,mm}',
    'fayecpp.h',
    'builds/ios/*.{h}',
    'src/*.{h,cpp}',
    'jansson/src/*.{h,c}',
    'libwebsockets/lib/*.{h}',
    'libwebsockets/lib/base64-decode.c',
    'libwebsockets/lib/client-handshake.c',
    'libwebsockets/lib/client-parser.c',
    'libwebsockets/lib/client.c',
    'libwebsockets/lib/context.c',
    'libwebsockets/lib/extension-deflate-frame.c',
    'libwebsockets/lib/extension-deflate-stream.c',
    'libwebsockets/lib/extension.c',
    'libwebsockets/lib/getifaddrs.c',
    'libwebsockets/lib/handshake.c',
    'libwebsockets/lib/header.c',
    'libwebsockets/lib/libwebsockets.c',
    'libwebsockets/lib/lws-plat-unix.c',
    'libwebsockets/lib/output.c',
    'libwebsockets/lib/parsers.c',
    'libwebsockets/lib/pollfd.c',
    'libwebsockets/lib/service.c',
    'libwebsockets/lib/sha-1.c',
    'libwebsockets/lib/alloc.c',
    'libwebsockets/lib/ssl.c'

  s.resources = 'contrib/objc/FayeCpp.bundle'
  s.compiler_flags = '-DHAVE_FAYECPP_CONFIG_H=1', '-DHAVE_CONFIG_H=1', '-DCMAKE_BUILD=1', '-DRE_HAVE_COREFOUNDATION_FRAMEWORK=1', '-DLWS_OPENSSL_SUPPORT=1' 
  s.xcconfig = { 'HEADER_SEARCH_PATHS' => '"${PODS_ROOT}/FayeCpp+OpenSSL/contrib/objc" "${PODS_ROOT}/FayeCpp+OpenSSL/libwebsockets/lib" "${PODS_ROOT}/FayeCpp+OpenSSL/jansson/src"' }
  s.libraries = 'z', 'stdc++'
  s.framework = 'CoreFoundation'
  s.requires_arc = true
  s.dependency 'OpenSSL'

end
