Pod::Spec.new do |s|
  s.name             = "blukiiSK"
  s.version          = "1.1.1"
  s.summary          = "blukiiSK is a library for a simple authentification with the blukii SmartKey"
  s.homepage         = "http://www.blukii.com/produkte/keys.html"
  s.documentation_url = "https://github.com/schneiderma/blukii_developer/tree/gh-pages/iOS/blukii-SmartKey-Framework"
  s.author           = { "blukii" => "support@blukii.com" }

  s.source           = { :git => "https://github.com/lennart683/blukiiSK.git", :tag => s.version.to_s }
  s.ios.source_files =  'blukiiSK/blukiiSK.framework/Versions/A/Headers/*.h'
  s.osx.source_files = 'blukiiSK_Mac/blukiiSK.framework/Versions/A/Headers/*.h'
  s.ios.vendored_frameworks = "blukiiSK/blukiiSK.framework"
  s.osx.vendored_frameworks = "blukiiSK_Mac/blukiiSK.framework"
  s.ios.deployment_target = '10.0'
  s.osx.deployment_target = '10.13'
  s.frameworks = 'CoreBluetooth'
  s.xcconfig = { 'LIBRARY_SEARCH_PATHS' => '"$(PODS_ROOT)/blukiiSK"',
                  'HEADER_SEARCH_PATHS' => '"$(PODS_ROOT)/Headers/blukiiSK"'}
  s.license      = { :type => 'Apache', :file => 'LICENSE' }
end
