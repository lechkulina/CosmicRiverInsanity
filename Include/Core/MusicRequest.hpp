/*
 *  MusicRequest.hpp
 *
 *  Created on: 3 cze 2014
 *  Author: Lech Kulina
 *  E-Mail: kulinalech@gmail.com
 */

#ifndef MUSICREQUEST_HPP_
#define MUSICREQUEST_HPP_

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>
#include <boost/parameter.hpp>
#include <Common/Keywords.hpp>
#include <Core/AbstractAsset.hpp>
#include <Core/AbstractRequest.hpp>

namespace Cosmic {

namespace Core {

    class MusicRequest;
    typedef boost::shared_ptr<MusicRequest> MusicRequestSharedPtr;
    typedef boost::weak_ptr<MusicRequest> MusicRequestWeakPtr;

    //! Executes a request to load texture from a local file system.
    class MusicRequest : public AbstractRequest {
        public:
            MusicRequest(const std::string& name,
                           const boost::filesystem::path& path);

            virtual bool isValid() const;
            virtual const std::string& getName() const;
            virtual const boost::filesystem::path& getPath() const;
            virtual void execute();

            BOOST_PARAMETER_MEMBER_FUNCTION(
                (MusicRequestSharedPtr), static make, Keywords::Tags,
                (required
                    (name, (const std::string&))
                    (path, (const boost::filesystem::path&))
                )
            ) {
                return boost::make_shared<MusicRequest>(name, path);
            }

        private:
            std::string name;
            boost::filesystem::path path;
    };

}

}

#endif /* MUSICREQUEST_HPP_ */
