
# By default, the Python virtualenv is created in the `venv` folder at the root
# of freedom-e-sdk. If you want your virtualenv to be placed somewhere else,
# set the FREEDOM_E_SDK_VENV_PATH environment variable.
FREEDOM_E_SDK_VENV_PATH ?= $(CURDIR)/venv

.PHONY: virtualenv
virtualenv: $(FREEDOM_E_SDK_VENV_PATH)/.stamp

.PHONY: clean-virtualenv
clean-virtualenv:
	-rm -rf $(FREEDOM_E_SDK_VENV_PATH)

# Freedom E SDK has two options for fetching Python dependencies:
#
#  1. Dependencies are fetched from the Python Package Index (PyPI) when the
#     virtualenv is created.
#  2. Dependencies are prefeteched from PyPI and stored in
#      FREEDOM_E_SDK_PIP_CACHE_PATH, then installed from there at virtualenv
#      creation time.
#
# By default, the pip-cache is created in the `pip-cache` folder at the root of
# freedom-e-sdk. If you want the pip-cache to be placed elsewhere, set the
# FREEDOM_E_SDK_PIP_CACHE_PATH environment variable.
FREEDOM_E_SDK_PIP_CACHE_PATH ?= pip-cache

$(FREEDOM_E_SDK_VENV_PATH)/bin/activate:
	python3 -m venv $(FREEDOM_E_SDK_VENV_PATH)
	. $@ && $(FREEDOM_E_SDK_VENV_PATH)/bin/python3 $(FREEDOM_E_SDK_VENV_PATH)/bin/pip install pip==20.0.1

.PHONY: pip-cache
pip-cache: $(FREEDOM_E_SDK_PIP_CACHE_PATH)/.stamp

$(FREEDOM_E_SDK_PIP_CACHE_PATH)/.stamp: $(FREEDOM_E_SDK_VENV_PATH)/bin/activate requirements.txt
	. $< && python3 scripts/download-python-packages.py requirements.txt $(FREEDOM_E_SDK_PIP_CACHE_PATH)
	touch $@

.PHONY: clean-pip-cache
clean-pip-cache:
	-rm -r $(FREEDOM_E_SDK_PIP_CACHE_PATH)

# If FREEDOM_E_SDK_PIP_CACHE_PATH does not exist, fetch dependencies from PyPI
ifeq ("$(wildcard $(FREEDOM_E_SDK_PIP_CACHE_PATH))","")

# We invoke pip as a script in order to avoid depending on the shebang line, which might
# exceed the 127-character limit depending on your environment.

$(FREEDOM_E_SDK_VENV_PATH)/.stamp: $(FREEDOM_E_SDK_VENV_PATH)/bin/activate requirements.txt
	@echo "################################################################################" >&2
	@echo "FREEDOM_E_SDK_PIP_CACHE not found, creating virtualenv from Python Package Index" >&2
	@echo "You can pre-download Python packages by running 'make pip-cache'."                >&2
	@echo "################################################################################" >&2
	. $< && $(FREEDOM_E_SDK_VENV_PATH)/bin/python3 $(FREEDOM_E_SDK_VENV_PATH)/bin/pip install pip==20.0.1
	. $< && $(FREEDOM_E_SDK_VENV_PATH)/bin/python3 $(FREEDOM_E_SDK_VENV_PATH)/bin/pip install -r requirements.txt
	touch $@

else # If FREEDOM_E_SDK_PIP_CACHE_PATH does exist, fetch dependences from there

# We invoke pip as a script in order to avoid depending on the shebang line, which might
# exceed the 127-character limit depending on your environment.

$(FREEDOM_E_SDK_VENV_PATH)/.stamp: $(FREEDOM_E_SDK_VENV_PATH)/bin/activate requirements.txt
	@echo "##################################################################" >&2
	@echo "FREEDOM_E_SDK_PIP_CACHE found, creating virtualenv from $(FREEDOM_E_SDK_PIP_CACHE_PATH)" >&2
	@echo "##################################################################" >&2
	. $< && $(FREEDOM_E_SDK_VENV_PATH)/bin/python3 $(FREEDOM_E_SDK_VENV_PATH)/bin/pip install --no-index --find-links $(FREEDOM_E_SDK_PIP_CACHE_PATH) -r requirements.txt
	touch $@

endif # FREEDOM_E_SDK_PIP_CACHE_PATH
