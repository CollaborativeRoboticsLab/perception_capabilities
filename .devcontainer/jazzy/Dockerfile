FROM ros:jazzy

# Add vscode user with same UID and GID as your host system
# (modified from https://code.visualstudio.com/remote/advancedcontainers/add-nonroot-user#_creating-a-nonroot-user)
# ubuntu now has a 1000 user ubuntu
ARG USERNAME=ubuntu
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# RUN groupadd --gid $USER_GID $USERNAME \
#     && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \

RUN apt-get update && apt-get upgrade -y \
    && apt-get install -y \
    sudo \
    git \
    curl \
    libcurl4-openssl-dev \
    libpoco-dev \
    nlohmann-json3-dev \
    ros-${ROS_DISTRO}-rmw-cyclonedds-cpp \
    ros-${ROS_DISTRO}-vision-opencv \
    ros-${ROS_DISTRO}-cv-bridge \
    ros-${ROS_DISTRO}-image-transport \
    ros-${ROS_DISTRO}-bondcpp \
    libportaudio2 \
    portaudio19-dev \
    python3-pyaudio \
    alsa-utils \
    pulseaudio-utils \
    && rm -rf /var/lib/apt/lists/* \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

RUN apt-get update && \
    apt-get install --no-install-recommends -y \
    ros-${ROS_DISTRO}-librealsense2* \
    ros-${ROS_DISTRO}-realsense2-* \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Create runtime directories for forwarded GUI/audio sockets
RUN mkdir -p /run/user/$USER_UID/pulse \
    && chown -R $USER_UID:$USER_GID /run/user/$USER_UID \
    && chmod 700 /run/user/$USER_UID \
    && chmod 700 /run/user/$USER_UID/pulse

# Switch from root to user
USER $USERNAME

# Rosdep update
RUN rosdep update

# Source the ROS setup file
RUN echo "source /opt/ros/${ROS_DISTRO}/setup.bash" >> ~/.bashrc

# make sure folders exist
WORKDIR /home/ubuntu/colcon_ws/src

RUN git clone https://github.com/CollaborativeRoboticsLab/capabilities2.git -b develop
# RUN git clone https://github.com/CollaborativeRoboticsLab/fabric.git -b develop
# RUN git clone https://github.com/CollaborativeRoboticsLab/fabric_capabilities.git
# RUN git clone --recurse-submodules https://github.com/CollaborativeRoboticsLab/prompt_tools.git
# RUN git clone https://github.com/CollaborativeRoboticsLab/prompt_capabilities.git
# RUN git clone https://github.com/CollaborativeRoboticsLab/perception.git

git clone https://github.com/CollaborativeRoboticsLab/fabric.git -b develop
git clone https://github.com/CollaborativeRoboticsLab/fabric_capabilities.git
git clone --recurse-submodules https://github.com/CollaborativeRoboticsLab/prompt_tools.git
git clone https://github.com/CollaborativeRoboticsLab/prompt_capabilities.git
git clone https://github.com/CollaborativeRoboticsLab/perception.git