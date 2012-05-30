Name:       vconf
Summary:    Configuration system library
Version:    0.2.23
Release:    1
Group:      System/Libraries
License:    Apache License, Version 2.0
Source0:    %{name}-%{version}.tar.gz
Source1001: packaging/vconf.manifest 
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  cmake
BuildRequires:  pkgconfig(elektra)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(dbus-1)
BuildRequires:  pkgconfig(dlog)
		
%description 
Configuration system library

%package devel
Summary:    vconf (devel)
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}
Requires:   pkgconfig(glib-2.0)
Requires:   vconf = %{version}-%{release}
Requires:   vconf-keys-devel = %{version}-%{release}

%description devel
Vconf library (devel)

%package keys-devel
Summary:    vconf (devel)
Group:      Development/Libraries
Requires:   %{name} = %{version}-%{release}
Requires:   vconf = %{version}-%{release}

%description keys-devel
Vconf key management header files

%prep
%setup -q -n %{name}-%{version}

%build
cp %{SOURCE1001} .
cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix}

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

mkdir -p %{buildroot}/opt/var/gconf
mkdir -p %{buildroot}/etc/rc.d/rc3.d
mkdir -p %{buildroot}/etc/rc.d/rc4.d
ln -sf /etc/rc.d/init.d/vconf-init %{buildroot}/etc/rc.d/rc3.d/S12vconf-init
ln -sf /etc/rc.d/init.d/vconf-init %{buildroot}/etc/rc.d/rc4.d/S12vconf-init

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%manifest vconf.manifest
%defattr(-,root,root,-)
%attr(755,root,root) %{_sysconfdir}/rc.d/init.d/vconf-init
%{_sysconfdir}/rc.d/rc3.d/S12vconf-init
%{_sysconfdir}/rc.d/rc4.d/S12vconf-init
%{_bindir}/vconftool
%attr(644, root, root) /opt/var/kdb/kdb_first_boot
%{_libdir}/*.so.*
%attr(777,root,root) /opt/var/gconf

%files devel
%manifest vconf.manifest
%defattr(-,root,root,-)
%{_includedir}/vconf/vconf.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/*.so

%files keys-devel
%manifest vconf.manifest
%defattr(-,root,root,-)
%{_includedir}/vconf/vconf-keys.h

