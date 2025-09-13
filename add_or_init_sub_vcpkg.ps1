
function add_sub_vcpkg {
    git submodule add https://github.com/microsoft/vcpkg.git .vcpkg
    .\.vcpkg\bootstrap-vcpkg.bat -disableMetrics
}
function init_sub_vcpkg {
    git submodule update --init --recursive
    .\.vcpkg\bootstrap-vcpkg.bat -disableMetrics
}

if (-not (Test-Path -Path ".\.vcpkg")) {
    add_sub_vcpkg
}
else {
    if (-not (Test-Path -Path ".\.vcpkg\vcpkg.exe")) {
        Write-Host "vcpkg.exe not found, initializing submodule..."
        init_sub_vcpkg
        return
    }
    Write-Host "vcpkg submodule already exists."
    Write-Host "If you want to reinitialize it, please delete the .vcpkg folder and run this script again."
}