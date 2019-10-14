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
                "target_type": "ANY",
                "target_lds": ["metal.ramrodata.lds", "metal.scratchpad.lds", "metal.default.lds"]}
    exports_sources = "update-targets.sh"
    license = "MIT"
    
    def build(self):
        
        if(self.settings.os_build != "Linux"):
            raise ConanInvalidConfiguration("unsupported os_build: %s" %
                                            (self.settings.os_build))
                                            
        # check that all options have been specified TO DO
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

        self.user_info.METAL_LDSCRIPT = os.path.join(self.package_folder, str(self.options.target_lds) )
        self.user_info.METAL_HEADER = os.path.join(self.package_folder,'include', 'metal.h')
        self.user_info.METAL_INLINE = os.path.join(self.package_folder,'include', 'metal-inline.h')
        self.user_info.PLATFORM_HEADER = os.path.join(self.package_folder,'include', 'metal-platform.h')
 
        lds_script = ["-T{lds_script}".format(lds_script=os.path.join(self.package_folder,str(self.options.target_lds)))]
 
        self.env_info.LDFLAGS += lds_script
        self.cpp_info.sharedlinkflags += lds_script  # linker flags
        self.cpp_info.exelinkflags += lds_script  # linker flags
 
    def requirements(self):
        self.requires("freedom-devicetree-tools/v201905@sifive/stable")
        
