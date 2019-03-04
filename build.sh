docker run --rm -v $(pwd):/work -v $(pwd)/.texmf-var:/root/.texmf-var vvakame/review:latest /bin/sh -c "cd /work/articles && review-pdfmaker config.yml"
