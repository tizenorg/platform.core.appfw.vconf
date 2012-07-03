Name:       vconf
Summary:    Configuration system library
Version:    0.2.23
Release:    1
Group:      System/Libraries
License:    Apache License, Version 2.0
Source0:    %{name}-%{version}.tar.gz
Source1:    vconf-setup.service
Source2:    vconf-setup.conf
Source1001: packaging/vconf.manifest
Requires(post): /sbin/ldconfig, systemd
Requires(postun): /sbin/ldconfig, systemd
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
mkdir -p %{buildroot}/opt/var/kdb/db
mkdir -p %{buildroot}%{_libdir}/systemd/system/basic.target.wants
mkdir -p %{buildroot}%{_libdir}/tmpfiles.d
install -m0644 %SOURCE1 %{buildroot}%{_libdir}/systemd/system/
install -m0644 %SOURCE2 %{buildroot}%{_libdir}/tmpfiles.d/
ln -sf ../vconf-setup.service %{buildroot}%{_libdir}/systemd/system/basic.target.wants/

mkdir -p %{buildroot}/etc/rc.d/rc3.d
mkdir -p %{buildroot}/etc/rc.d/rc4.d
ln -sf /etc/rc.d/init.d/vconf-init %{buildroot}/etc/rc.d/rc3.d/S12vconf-init
ln -sf /etc/rc.d/init.d/vconf-init %{buildroot}/etc/rc.d/rc4.d/S12vconf-init


%post
/sbin/ldconfig
systemctl daemon-reload

%postun
/sbin/ldconfig
systemctl daemon-reload


%files
%defattr(-,root,root,-)
%manifest vconf.manifest
%attr(755,root,root) %{_sysconfdir}/rc.d/init.d/vconf-init
%{_sysconfdir}/rc.d/rc3.d/S12vconf-init
%{_sysconfdir}/rc.d/rc4.d/S12vconf-init
%{_bindir}/vconftool
%config(missingok) %attr(644,root,root) /opt/var/kdb/kdb_first_boot
%{_libdir}/*.so.*
%dir %attr(777,root,root) /opt/var/gconf
%dir %attr(777,root,root) /opt/var/kdb/db
%{_libdir}/systemd/system/basic.target.wants/vconf-setup.service
%{_libdir}/systemd/system/vconf-setup.service
%{_libdir}/tmpfiles.d/vconf-setup.conf

%files devel
%defattr(-,root,root,-)
%manifest vconf.manifest
%{_includedir}/vconf/vconf.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/*.so

%files keys-devel
%defattr(-,root,root,-)
%manifest vconf.manifest
%{_includedir}/vconf/vconf-keys.h

