import os
from conans import ConanFile
from conans.errors import ConanInvalidConfiguration
from conans.tools import os_info, SystemPackageTool

class FreedomBSPConan(ConanFile):
    name = "freedom-bsp"
    version = "v201905"
    settings = "os_build"
    url = None # We might consider pointing on toolchain repo here
    description = """Freedom devicetree tools package"""
    options = { "target_dts": "ANY",
                "target_name": "ANY",
                "target_type": "ANY"}
    exports_sources = "update-targets.sh"
    license = "MIT"
    
    def build(self):
        
        if(self.settings.os_build != "Linux"):
            raise ConanInvalidConfiguration("unsupported os_build: %s" %
                                            (self.settings.os_build))
                                            
        # check that all option add been specified TO DO
        self.run("./update-targets.sh --target-name {target_name} --target-type {target_type} --target-dts {target_dts} --sdk-path .".format(
            target_name=self.options.target_name, 
            target_type=self.options.target_type,
            target_dts=self.options.target_dts))

    def package(self):
        # Copy metal includes
        self.copy("*.h", dst="include", src="", keep_path=False)
        self.copy("*", dst="", src="", excludes="*.h", keep_path=False)
        
    def package_info(self):
        if(self.settings.os_build != "Linux"):
            raise ConanInvalidConfiguration("unsupported os_build: %s" %
                                            (self.settings.os_build))
        self.cpp_info.includedirs = ['include']  # Ordered list of include paths

        self.user_info.METAL_LDSCRIPT = os.path.join(self.package_folder,'metal.default.lds' )
        self.user_info.METAL_HEADER = os.path.join(self.package_folder,'include', 'metal.h')
        self.user_info.METAL_INLINE = os.path.join(self.package_folder,'include', 'metal-inline.h')
        self.user_info.PLATFORM_HEADER = os.path.join(self.package_folder,'include', 'metal-platform.h')
 
    def requirements(self):
        self.requires("freedom-devicetree-tools/v201905@sifive/stable")
        
