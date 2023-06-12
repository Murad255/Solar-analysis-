
FROM nvidia/cuda:10.0-cudnn7-devel-ubuntu18.04
RUN nvcc --version
ARG USER=user
ARG PASSWORD=${USER}123456$
# Install ubuntu packages
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        build-essential \
        git \
        curl \
        ca-certificates \
        sudo \
        locales \
        openssh-server \
        vim && \
    # Remove the effect of `apt-get update`
    rm -rf /var/lib/apt/lists/* && \
    # Make the "en_US.UTF-8" locale
    localedef -i en_US -c -f UTF-8 -A /usr/share/locale/locale.alias en_US.UTF-8
ENV LANG en_US.utf8
ENV TZ=Europe/Brussels
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update --fix-missing && DEBIAN_FRONTEND=noninteractive apt-get install --assume-yes \
   build-essential \
   python3 \
   python3-dev \
   python3-pip \
   ffmpeg libsm6 libxext6
 
# Create an user for the app.
RUN useradd --create-home --shell /bin/bash --groups sudo ${USER}
RUN echo ${USER}:${PASSWORD} | chpasswd
USER ${USER}
ENV HOME /home/${USER}
WORKDIR $HOME
RUN curl -o miniconda.sh https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh && \
    chmod +x miniconda.sh && \
    /bin/bash miniconda.sh -b -p conda && \
    rm miniconda.sh
RUN touch $HOME/.bashrc && \
    echo "export PATH=$HOME/conda/bin:$PATH" >> $HOME/.bashrc
ENV PATH $HOME/conda/bin:$PATH
RUN conda/bin/conda init bash
COPY . .
RUN conda create --name solar python=3.10.9
RUN conda run -n solar python -m pip install -r requirements_docker.txt
# Activate the environment, and make sure it's activated:
RUN echo "conda activate solar" > ~/.bashrc
