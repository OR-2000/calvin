rm -rf src obj
cp -r src_pdlr/ src
cp definitions.hh src/common/definitions.hh
cd src
make clean
make -j
cd ../
bin/deployment/db 0 m 0