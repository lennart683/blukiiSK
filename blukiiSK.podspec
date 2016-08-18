Pod::Spec.new do |s|
  s.name             = "blukiiSK"
  s.version          = "1.0.0"
  s.summary          = "blukiiSK"
  s.homepage         = "https://www.blukii.com/"
  s.author           = { "blukii" => "support@blukii.com" }
  s.platform         = :ios
  s.source           = { :git => "https://github.com/lennart683/blukiiSK.git", :tag => s.version.to_s }
  s.source_files     =  'blukiiSK/blukiiSK.framework/Versions/A/Headers/*.h'
  s.vendored_frameworks = "blukiiSK/blukiiSK.framework"
  s.ios.deployment_target = '8.4'
  s.frameworks = 'CoreBluetooth'
  s.xcconfig = { 'LIBRARY_SEARCH_PATHS' => '"$(PODS_ROOT)/blukiiSK"', 
                  'HEADER_SEARCH_PATHS' => '"$(PODS_ROOT)/Headers/blukiiSK"'}
  s.license      = { :type => 'Apache', :file => 'LICENSE' }
end
