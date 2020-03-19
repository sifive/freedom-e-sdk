
# By default, the Python virtualenv is created in the `venv` folder at the root
# of freedom-e-sdk. If you want your virtualenv to be placed somewhere else,
# set the FREEDOM_E_SDK_VENV_PATH environment variable.
FREEDOM_E_SDK_VENV_PATH ?= venv

.PHONY: virtualenv
virtualenv: $(FREEDOM_E_SDK_VENV_PATH)/.stamp

# Just in case the cached dependencies fail, users can install Python packages
# from the Python Package Index by running `make virtualenv-from-pypi`

.PHONY: virtualenv-from-pypi

# invoke python3 pip in order to bypass 127 character limit in shebang
virtualenv-from-pypi: $(FREEDOM_E_SDK_VENV_PATH)/bin/activate requirements.txt
	. $< && $(FREEDOM_E_SDK_VENV_PATH)/bin/python3 $(FREEDOM_E_SDK_VENV_PATH)/bin/pip install --upgrade pip
	. $< && $(FREEDOM_E_SDK_VENV_PATH)/bin/python3 $(FREEDOM_E_SDK_VENV_PATH)/bin/pip install -r requirements.txt

$(FREEDOM_E_SDK_VENV_PATH)/.stamp: $(FREEDOM_E_SDK_VENV_PATH)/bin/activate requirements.txt
	. $< && $(FREEDOM_E_SDK_VENV_PATH)/bin/python3 $(FREEDOM_E_SDK_VENV_PATH)/bin/pip install --no-index --find-links pip-cache --upgrade pip
	. $< && $(FREEDOM_E_SDK_VENV_PATH)/bin/python3 $(FREEDOM_E_SDK_VENV_PATH)/bin/pip install --no-index --find-links pip-cache -r requirements.txt
	touch $@

$(FREEDOM_E_SDK_VENV_PATH)/bin/activate:
	python3 -m venv $(FREEDOM_E_SDK_VENV_PATH)

# The pip-cache directory holds a cache of all the Python package dependencies, being careful
# that all are platform-indepentent.
#
# The result should be that when freedom-e-sdk is cloned, the virtualenv is created simply
# by installing all cached dependencies from the submodule
#
# The pip-cache can be updated when requirements.txt changes by running `make update-pip-cache`,
# commiting the changes to the submodule, and bumping the submodule.

.PHONY: update-pip-cache
update-pip-cache: requirements.txt
	./pip-cache/download-python-dependencies.py $<

.PHONY: clean-pip-cache
clean-pip-cache:
	-rm -rf pip-cache/*.whl pip-cache *.tar.gz

.PHONY: clean-virtualenv
clean-virtualenv:
	-rm -rf $(FREEDOM_E_SDK_VENV_PATH)

