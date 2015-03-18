# Declare function vcs_renum(<vcs_type>, <work_dir>)
#     Returns the last revision number of a repository under version control
#     param vcs_type : name of the VCS, must be one of bzr|svn|git
#     param work_dir : optional path to the repository ("." if not specified)

defineReplace(vcs_revnum) {
    !isEmpty(2) {
        VCS_WORKDIR = $$2
    } else {
        VCS_WORKDIR = .
    }
    VCS_WORKDIR = $$system_path($$absolute_path($$VCS_WORKDIR))

    VCS_OUTPUT =
    equals(1, bzr):VCS_OUTPUT = $$system(bzr revno $$VCS_WORKDIR)
    equals(1, svn):VCS_OUTPUT = $$system(svnversion -n $$VCS_WORKDIR)
    equals(1, git) {
        SYS_CMD_SEP = ;
        win32:SYS_CMD_SEP = &

        CMD_CD_VCS_WORKDIR = cd $$VCS_WORKDIR
        # ">nul 2>&1" : Redirect error and output to NUL
        win32:CMD_CD_VCS_WORKDIR = cd /D $$VCS_WORKDIR >nul 2>&1

        VCS_OUTPUT = $$system($$CMD_CD_VCS_WORKDIR  $$SYS_CMD_SEP  git rev-parse --short HEAD)
    }

    return($$find(VCS_OUTPUT, [0-9a-zA-Z]*))
}
