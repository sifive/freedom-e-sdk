
.PHONY: virtualenv
virtualenv: venv/.stamp

venv/.stamp: venv/bin/activate pip-cache requirements.txt
	. $< && pip install --no-index --find-links pip-cache --upgrade pip
	. $< && pip install --no-index --find-links pip-cache -r requirements.txt
	touch $@

venv/bin/activate:
	python3 -m venv venv

# The pip-cache directory holds a cache of all the Python package dependencies, being careful
# that all are platform-indepentent.
#
# The result should be that when freedom-e-sdk is cloned, the virtualenv is created simply
# by caching all dependencies in pip-cache and then installing them.
#
# This allows freedom-e-sdk to be packaged for customer deliveries with all dependencies
# pre-cached and available for offline installation. Simply run `make pip-cache` or any build
# that depends on the `pip-cache` or `virtualenv` targets and then include the pip-cache directory
# in the archived SDK.

pip-cache: requirements.txt
	python3 -m venv venv
	mkdir -p $@
	. venv/bin/activate && pip install --upgrade pip
	. venv/bin/activate && pip download -d $@ -r requirements.txt --platform any --no-deps

.PHONY: clean-pip-cache
clean-pip-cache:
	-rm -rf pip-cache

.PHONY: clean-virtualenv
clean-virtualenv:
	-rm -rf venv

