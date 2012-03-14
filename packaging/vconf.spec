Name:       vconf
Summary:    Configuration system library
Version:    0.2.21
Release:    1
Group:      System/Libraries
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Requires(post): /sbin/ldconfig, /bin/ln
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
cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix}


make %{?jobs:-j%jobs}

%install
%make_install

mkdir -p %{buildroot}/opt/var/gconf
mkdir -p %{buildroot}/opt/var/kdb/db
chmod 777 %{buildroot}/opt/var/kdb/db

%post 
/sbin/ldconfig

ln -sf /etc/rc.d/init.d/vconf-init /etc/rc.d/rc3.d/S12vconf-init
ln -sf /etc/rc.d/init.d/vconf-init /etc/rc.d/rc4.d/S12vconf-init


%postun -p /sbin/ldconfig

%files
%{_sysconfdir}/rc.d/init.d/vconf-init
%{_bindir}/vconftool
%config(missingok) %attr(644,root,root) /opt/var/kdb/kdb_first_boot
%{_libdir}/*.so.*
%dir %attr(777,root,root) /opt/var/gconf
%dir %attr(777,root,root) /opt/var/kdb/db

%files devel
%{_includedir}/vconf/vconf.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/*.so

%files keys-devel
%{_includedir}/vconf/vconf-keys.h

