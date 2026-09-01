r=/home/olorochi/repos
export KISS_PATH=$r/local/repo/extra:$r/local/personal:$r/local/school:$r/repo/core:$r/repo/extra:$r/repo/wayland:$r/community/community

export MAKEFLAGS="-j 4"
export SAMUFLAGS="-j 4"
export COMMON_FLAGS="-O2 -pipe -march=alderlake -mno-cldemote -mno-kl -mno-pconfig -mno-sgx -mno-widekl -mshstk"
export CFLAGS="$COMMON_FLAGS"
export CXXFLAGS="$COMMON_FLAGS"
export FCFLAGS="$COMMON_FLAGS"
export FFLAGS="$COMMON_FLAGS"
export RUSTFLAGS="$RUSTFLAGS -C target-cpu=native"

export HOSTNAME=$(cat /proc/sys/kernel/hostname)
export PATH=~/scripts:$PATH
export EDITOR=vim
export PAGER="vim -R -"
export MANPAGER="less"

export XDG_RUNTIME_DIR=/tmp/$(id -u)-runtime-dir
if ! test -d "${XDG_RUNTIME_DIR}"; then
    mkdir "${XDG_RUNTIME_DIR}"
    chmod 0700 "${XDG_RUNTIME_DIR}"
fi

export HISTFILE=~/.cache/histfile
export HISTSIZE=10000
export SAVEHIST=100000

export ENV=$HOME/config/kshrc
export XDG_CONFIG_HOME=~/config

[[ $(tty) = "/dev/tty1" ]] && exec sway # !! EXEC !!
return 0
