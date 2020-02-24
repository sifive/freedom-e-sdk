
.PHONY: virtualenv
virtualenv: venv/.stamp

# Just in case the cached dependencies fail, users can install Python packages
# from the Python Package Index by running `make virtualenv-from-pypi`

.PHONY: virtualenv-from-pypi
virtualenv-from-pypi: venv/bin/activate requirements.txt
	. $< && pip install --upgrade pip
	. $< && pip install -r requirements.txt

venv/.stamp: venv/bin/activate requirements.txt
	. $< && pip install --no-index --find-links pip-cache --upgrade pip
	. $< && pip install --no-index --find-links pip-cache -r requirements.txt
	touch $@

venv/bin/activate:
	python3 -m venv venv

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
	-rm -rf venv

