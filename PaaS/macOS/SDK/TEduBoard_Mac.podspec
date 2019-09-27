Pod::Spec.new do |spec|
  spec.name         = 'TEduBoard_Mac'
  spec.version      = '2.3.4'
  spec.platform     = :osx 
  spec.osx.deployment_target = '10.10'
  spec.license      = { :type => 'Proprietary',
      :text => <<-LICENSE
        copyright 2017 tencent Ltd. All rights reserved.
        LICENSE
       }
  spec.homepage     = 'https://cloud.tencent.com/document/product/680/14776'
  spec.documentation_url = 'https://cloud.tencent.com/document/product/680/35891'
  spec.authors      = 'tencent interact class'
  spec.summary      = 'TXIMSDK_Mac'
  
  spec.requires_arc = true

  spec.source = { :git => 'https://github.com/tencentyun/TIC.git', :tag => spec.version}
  spec.preserve_paths = 'PaaS/macOS/SDK/TEduBoard_Mac.framework'
  spec.source_files = 'PaaS/macOS/SDK/TEduBoard_Mac.framework/Versions/A/Headers/*.h'
  spec.public_header_files = 'PaaS/macOS/SDK/TEduBoard_Mac.framework/Versions/A/Headers/*.h'
  spec.vendored_frameworks = 'PaaS/macOS/SDK/TEduBoard_Mac.framework'
  spec.xcconfig = { 'HEADER_SEARCH_PATHS' => '${PODS_ROOT}/TEduBoard_Mac/macOS/SDK/TEduBoard_Mac.framework/Versions/A/Headers/'}
end
