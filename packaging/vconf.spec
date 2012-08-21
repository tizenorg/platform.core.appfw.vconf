Name:       vconf
Summary:    Configuration system library
Version:    0.2.26
Release:    1
Group:      System/Libraries
License:    Apache License, Version 2.0
Source0:    %{name}-%{version}.tar.gz
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  cmake
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(vconf-internal-keys)
		
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
Requires:   vconf-internal-keys-devel

%description keys-devel
Vconf key management header files

%prep
%setup -q -n %{name}-%{version}

%build
cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix}

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

mkdir -p %{buildroot}/etc/rc.d/rc3.d
mkdir -p %{buildroot}/etc/rc.d/rc4.d
ln -sf /etc/rc.d/init.d/vconf-init %{buildroot}/etc/rc.d/rc3.d/S04vconf-init
ln -sf /etc/rc.d/init.d/vconf-init %{buildroot}/etc/rc.d/rc4.d/S04vconf-init

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%attr(755,root,root) %{_sysconfdir}/rc.d/init.d/vconf-init
%{_sysconfdir}/rc.d/rc3.d/S04vconf-init
%{_sysconfdir}/rc.d/rc4.d/S04vconf-init
%{_bindir}/vconftool
%attr(644, root, root) /opt/var/kdb/kdb_first_boot
%{_libdir}/*.so.*

%files devel
%defattr(-,root,root,-)
%{_includedir}/vconf/vconf.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/*.so

%files keys-devel
%defattr(-,root,root,-)
%{_includedir}/vconf/vconf-keys.h

%changelog
* Tue Aug 14 2012 - Hyungdeuk Kim <hd3.kim@samsung.com>
- Fix issues related prevent
- Fix warning msg at build time

* Mon Jul 23 2012 - SeungYeup Kim <sy2004.kim@samsung.com>
- Enable -f option for force update
